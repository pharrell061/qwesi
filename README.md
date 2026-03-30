# Qcodespace

A collection of projects including indoor navigation and school assignments.

## Projects

### Indoor Navigation (indoornav/)
A Django-based backend with a React frontend for indoor navigation mapping and pathfinding.

**Technologies:**
- Backend: Django, Python
- Frontend: React, Vite, Tailwind CSS
- Features: QR code scanning, indoor routing using Dijkstra's algorithm

### School Assignments (school/)
Various C++ programming assignments and exercises.

**Contents:**
- zadacha2.cpp - Magic Sum Calculator: Sums odd numbers containing a specific digit

## Setup & Installation

### Backend
```bash
cd indoornav/backend
pip install -r requirements.txt
python manage.py runserver
```

### Frontend
```bash
cd indoornav/frontend
npm install
npm run dev
```

### C++ Programs
```bash
cd school/z2
g++ -std=c++11 zadacha2.cpp -o zadacha2
./zadacha2
```

## License
MIT
