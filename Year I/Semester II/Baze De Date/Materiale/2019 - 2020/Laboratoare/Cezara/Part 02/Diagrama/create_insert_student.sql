-- script to create NORTHWOODS database
-- revised 8/17/2002 JM 
-- modified 3/17/2004 LM

DROP TABLE enrollment CASCADE CONSTRAINTS;
DROP TABLE course_section CASCADE CONSTRAINTS;
DROP TABLE term CASCADE CONSTRAINTS;
DROP TABLE course CASCADE CONSTRAINTS;
DROP TABLE student CASCADE CONSTRAINTS;
DROP TABLE faculty CASCADE CONSTRAINTS;
DROP TABLE location CASCADE CONSTRAINTS;

CREATE TABLE LOCATION
(loc_id NUMBER(6),
bldg_code VARCHAR2(10),
room VARCHAR2(6),
capacity NUMBER(5), 
CONSTRAINT location_loc_id_pk PRIMARY KEY (loc_id));

CREATE TABLE faculty
(f_id NUMBER(6),
f_last VARCHAR2(30),
f_first VARCHAR2(30),
f_mi CHAR(1),
loc_id NUMBER(5),
f_phone VARCHAR2(10),
f_rank VARCHAR2(9),
f_super NUMBER(6), 
f_pin NUMBER(4),
f_image BLOB, 
CONSTRAINT faculty_f_id_pk PRIMARY KEY(f_id),
CONSTRAINT faculty_loc_id_fk FOREIGN KEY (loc_id) REFERENCES location(loc_id));

CREATE TABLE student
(s_id VARCHAR2(6),
s_last VARCHAR2(30),
s_first VARCHAR2(30),
s_mi CHAR(1),
s_address VARCHAR2(25),
s_city VARCHAR2(20),
s_state CHAR(2),
s_zip VARCHAR2(10),
s_phone VARCHAR2(10),
s_class CHAR(2),
s_dob DATE,
s_pin NUMBER(4),
f_id NUMBER(6),
time_enrolled INTERVAL YEAR TO MONTH,
CONSTRAINT student_s_id_pk PRIMARY KEY (s_id),
CONSTRAINT student_f_id_fk FOREIGN KEY (f_id) REFERENCES faculty(f_id));

CREATE TABLE TERM
(term_id NUMBER(6),
term_desc VARCHAR2(20),
status VARCHAR2(20),
start_date DATE,
CONSTRAINT term_term_id_pk PRIMARY KEY (term_id),
CONSTRAINT term_status_cc CHECK ((status = 'OPEN') OR (status = 'CLOSED')));

CREATE TABLE COURSE
(course_no VARCHAR2(7),
course_name VARCHAR2(25),
credits NUMBER(2),
CONSTRAINT course_course_id_pk PRIMARY KEY(course_no));

CREATE TABLE COURSE_SECTION
(c_sec_id NUMBER(6),
course_no VARCHAR2(7) CONSTRAINT course_section_courseid_nn NOT NULL,
term_id NUMBER(6) CONSTRAINT course_section_termid_nn NOT NULL,
sec_num NUMBER(2) CONSTRAINT course_section_secnum_nn NOT NULL,
f_id NUMBER(6),
c_sec_day VARCHAR2(10),
c_sec_time DATE,
c_sec_duration INTERVAL DAY TO SECOND,
loc_id NUMBER(6),
max_enrl NUMBER(4) CONSTRAINT course_section_maxenrl_nn NOT NULL,
CONSTRAINT course_section_csec_id_pk PRIMARY KEY (c_sec_id),
CONSTRAINT course_section_cid_fk FOREIGN KEY (course_no) REFERENCES course(course_no), 	
CONSTRAINT course_section_loc_id_fk FOREIGN KEY (loc_id) REFERENCES location(loc_id),
CONSTRAINT course_section_termid_fk FOREIGN KEY (term_id) REFERENCES term(term_id),
CONSTRAINT course_section_fid_fk FOREIGN KEY (f_id) REFERENCES faculty(f_id));

CREATE TABLE ENROLLMENT
(s_id VARCHAR2(6),
c_sec_id NUMBER(6),
grade CHAR(1),
CONSTRAINT enrollment_pk PRIMARY KEY (s_id, c_sec_id),
CONSTRAINT enrollment_sid_fk FOREIGN KEY (s_id) REFERENCES student(s_id),
CONSTRAINT enrollment_csecid_fk FOREIGN KEY (c_sec_id) REFERENCES course_section (c_sec_id));



---- inserting into LOCATION table
INSERT INTO location VALUES
(1, 'CR', '101', 150);

INSERT INTO location VALUES
(2, 'CR', '202', 40);

INSERT INTO location VALUES
(3, 'CR', '103', 35);

INSERT INTO location VALUES
(4, 'CR', '105', 35);

INSERT INTO location VALUES
(5, 'BUS', '105', 42);

INSERT INTO location VALUES
(6, 'BUS', '404', 35);

INSERT INTO location VALUES
(7, 'BUS', '421', 35);

INSERT INTO location VALUES
(8, 'BUS', '211', 55);

INSERT INTO location VALUES
(9, 'BUS', '424', 1);

INSERT INTO location VALUES
(10, 'BUS', '402', 1);

INSERT INTO location VALUES
(11, 'BUS', '433', 1);

INSERT INTO location VALUES
(12, 'LIB', '217', 2);

INSERT INTO location VALUES
(13, 'LIB', '222', 1);


--- inserting records into FACULTY
INSERT INTO faculty VALUES
(1, 'Marx', 'Teresa', 'J', 9, '4075921695', 'Associate', 4, 6338, EMPTY_BLOB());

INSERT INTO faculty VALUES
(2, 'Zhulin', 'Mark', 'M', 10, '4073875682', 'Full', NULL, 1121, EMPTY_BLOB());

INSERT INTO faculty VALUES
(3, 'Langley', 'Colin', 'A', 12, '4075928719', 'Assistant', 4, 9871, EMPTY_BLOB());

INSERT INTO faculty VALUES
(4, 'Brown', 'Jonnel', 'D', 11, '4078101155', 'Full', NULL, 8297, EMPTY_BLOB());

INSERT INTO faculty VALUES
(5, 'Sealy', 'James', 'L', 13, '4079817153', 'Associate', 1, 6089, EMPTY_BLOB());

--- inserting records into STUDENT
INSERT INTO student VALUES
('JO100', 'Jones', 'Tammy', 'R', '1817 Eagleridge Circle', 'Tallahassee', 
'FL', '32811', '7155559876', 'SR', TO_DATE('07/14/1985', 'MM/DD/YYYY'), 8891, 1, TO_YMINTERVAL('3-2'));

INSERT INTO student VALUES
('PE100', 'Perez', 'Jorge', 'C', '951 Rainbow Dr', 'Clermont', 
'FL', '34711', '7155552345', 'SR', TO_DATE('08/19/1985', 'MM/DD/YYYY'), 1230, 1, TO_YMINTERVAL('4-2'));

INSERT INTO student VALUES
('MA100', 'Marsh', 'John', 'A', '1275 West Main St', 'Carrabelle', 
'FL', '32320', '7155553907', 'JR', TO_DATE('10/10/1982', 'MM/DD/YYYY'), 1613, 1, TO_YMINTERVAL('3-0'));

INSERT INTO student VALUES
('SM100', 'Smith', 'Mike', NULL, '428 Markson Ave', 'Eastpoint', 
'FL', '32328', '7155556902', 'SO', TO_DATE('09/24/1986', 'MM/DD/YYYY'), 1841, 2, TO_YMINTERVAL('2-2'));

INSERT INTO student VALUES
('JO101', 'Johnson', 'Lisa', 'M', '764 Johnson Place', 'Leesburg', 
'FL', '34751', '7155558899', 'SO', TO_DATE('11/20/1986', 'MM/DD/YYYY'), 4420, 4, TO_YMINTERVAL('1-11'));

INSERT INTO student VALUES
('NG100', 'Nguyen', 'Ni', 'M', '688 4th Street', 'Orlando', 
'FL', '31458', '7155554944', 'FR', TO_DATE('12/4/1986', 'MM/DD/YYYY'), 9188, 3, TO_YMINTERVAL('0-4'));

--- inserting records into TERM
INSERT INTO term (term_id, term_desc, status) VALUES 
(1, 'Fall 2005', 'CLOSED');

INSERT INTO term (term_id, term_desc, status) VALUES
(2, 'Spring 2006', 'CLOSED');

INSERT INTO term (term_id, term_desc, status) VALUES
(3, 'Summer 2006', 'CLOSED');

INSERT INTO term (term_id, term_desc, status) VALUES
(4, 'Fall 2006', 'CLOSED');

INSERT INTO term (term_id, term_desc, status) VALUES
(5, 'Spring 2007', 'CLOSED');

INSERT INTO term (term_id, term_desc, status) VALUES
(6, 'Summer 2007', 'OPEN');

--- inserting records into COURSE
INSERT INTO course VALUES
('MIS 101', 'Intro. to Info. Systems', 3);

INSERT INTO course VALUES
('MIS 301', 'Systems Analysis', 3);

INSERT INTO course VALUES
('MIS 441', 'Database Management', 3);

INSERT INTO course VALUES
('CS 155', 'Programming in C++', 3);

INSERT INTO course VALUES
('MIS 451', 'Web-Based Systems', 3);

--- inserting records into COURSE_SECTION
INSERT INTO course_section VALUES
(1, 'MIS 101', 4, 1, 2, 'MWF', TO_DATE('10:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:00:50.00'), 1, 140);

INSERT INTO course_section VALUES
(2, 'MIS 101', 4, 2, 3, 'TR', TO_DATE('09:30 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:15.00'), 7, 35);

INSERT INTO course_section VALUES
(3, 'MIS 101', 4, 3, 3, 'MWF', TO_DATE('08:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:00:50.00'), 2, 35);

INSERT INTO course_section VALUES
(4, 'MIS 301', 4, 1, 4, 'TR', TO_DATE('11:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:15.00'), 6, 35);

INSERT INTO course_section VALUES
(5, 'MIS 301', 5, 2, 4, 'TR', TO_DATE('02:00 PM', 'HH:MI PM'), TO_DSINTERVAL('0 00:01:15.00'), 6, 35);

INSERT INTO course_section VALUES
(6, 'MIS 441', 5, 1, 1, 'MWF', TO_DATE('09:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:00:50.00'), 5, 30);

INSERT INTO course_section VALUES
(7, 'MIS 441', 5, 2, 1, 'MWF', TO_DATE('10:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:00:50.00'), 5, 30);

INSERT INTO course_section VALUES
(8, 'CS 155', 5, 1, 5, 'TR', TO_DATE('08:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:15.00'), 3, 35);

INSERT INTO course_section VALUES
(9, 'MIS 451', 5, 1, 2, 'MWF', TO_DATE('02:00 PM', 'HH:MI PM'), TO_DSINTERVAL('0 00:00:50.00'), 5, 35);

INSERT INTO course_section VALUES
(10, 'MIS 451', 5, 2, 2, 'MWF', TO_DATE('03:00 PM', 'HH:MI PM'), TO_DSINTERVAL('0 00:00:50.00'), 5, 35);

INSERT INTO course_section VALUES
(11, 'MIS 101', 6, 1, 1, 'MTWRF', TO_DATE('08:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:30.00'), 1, 50);

INSERT INTO course_section VALUES
(12, 'MIS 301', 6, 1, 2, 'MTWRF', TO_DATE('08:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:30.00'), 6, 35);

INSERT INTO course_section VALUES
(13, 'MIS 441', 6, 1, 3, 'MTWRF', TO_DATE('09:00 AM', 'HH:MI AM'), TO_DSINTERVAL('0 00:01:30.00'), 5, 35);

--- inserting records into ENROLLMENT
INSERT INTO enrollment VALUES
('JO100', 1, 'A');

INSERT INTO enrollment VALUES
('JO100', 4, 'A');

INSERT INTO enrollment VALUES
('JO100', 6, 'B');

INSERT INTO enrollment VALUES
('JO100', 9, 'B');

INSERT INTO enrollment VALUES
('PE100', 1, 'C');

INSERT INTO enrollment VALUES
('PE100', 5, 'B');

INSERT INTO enrollment VALUES
('PE100', 6, 'A');

INSERT INTO enrollment VALUES
('PE100', 9, 'B');

INSERT INTO enrollment VALUES
('MA100', 1, 'C');

INSERT INTO enrollment VALUES
('MA100', 12, NULL);

INSERT INTO enrollment VALUES
('MA100', 13, NULL);

INSERT INTO enrollment VALUES
('SM100', 11, NULL);

INSERT INTO enrollment VALUES
('SM100', 12, NULL);

INSERT INTO enrollment VALUES
('JO101', 1, 'B');

INSERT INTO enrollment VALUES
('JO101', 5, 'C');

INSERT INTO enrollment VALUES
('JO101', 9, 'C');

INSERT INTO enrollment VALUES
('JO101', 11, NULL);

INSERT INTO enrollment VALUES
('JO101', 13, NULL);

INSERT INTO enrollment VALUES
('NG100', 11, NULL);

INSERT INTO enrollment VALUES
('NG100', 12, NULL);

COMMIT;
