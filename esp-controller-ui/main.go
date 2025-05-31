/*
   Control status file creation/deletion via web interface
*/

package main

import (
	"bufio"
	"html/template"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"unicode"
	"unicode/utf8"
)

const (
	fileList = "/etc/esp-controller/filelist.txt"
	dir      = "/var/lib/esp-controller"
)

type FileEntry struct {
	Name    string
	Checked bool
}

var tmpl = template.Must(template.ParseFiles("/usr/share/esp-controller-ui/templates/index.html"))

func main() {
	http.HandleFunc("/", handleIndex)
	http.HandleFunc("/toggle", handleToggle)
	http.ListenAndServe(":6060", nil)
}

func readFileList() ([]string, error) {
	f, err := os.Open(fileList)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	var files []string
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		r, _ := utf8.DecodeRuneInString(line)
		if !unicode.IsLetter(r) {
			continue
		}
		files = append(files, line)
	}
	return files, scanner.Err()
}

func handleIndex(w http.ResponseWriter, r *http.Request) {
	files, err := readFileList()
	if err != nil {
		http.Error(w, "Could not read file list", 500)
		return
	}
	var entries []FileEntry
	for _, name := range files {
		filePath := filepath.Join(dir, name)
		checked := false
		if _, err := os.Stat(filePath); err == nil {
			checked = true
		}
		entries = append(entries, FileEntry{Name: name, Checked: checked})
	}
	tmpl.Execute(w, entries)
}

func handleToggle(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Redirect(w, r, "/", http.StatusSeeOther)
		return
	}
	r.ParseForm()
	name := r.FormValue("name")
	checked := r.FormValue("checked") == "true"
	filePath := filepath.Join(dir, name)
	if checked {
		os.MkdirAll(dir, 0755)
		os.WriteFile(filePath, []byte("checked"), 0644)
	} else {
		os.Remove(filePath)
	}
	http.Redirect(w, r, "/", http.StatusSeeOther)
}
