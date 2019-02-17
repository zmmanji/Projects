-------------------------------------Q1--------------------------------------------------

SELECT name, COUNT(*) as NumberOfMovies  
FROM ActedIn   
GROUP BY name 
ORDER BY COUNT(*) DESC

--------------------------------------Q2-------------------------------------------------------------

select A.name, COUNT(*) Count_NumberOfMovies
from Actors A, ActedIn B
where A.name=B.name
group by A.name
having count(*) >1
order by count(*) DESC

---------------------------------------Q3---------------------------------------------------------------------
with ActorsMovies (name,numberMovies) as
(select A.name, count(*) as numberMovies
from ActedIn A ,Actors B
where A.name=B.name
group by A.name)
select name,numberMovies
from ActorsMovies
where numberMovies=(select max(numberMovies) from ActorsMovies);

-----------------------------------------Q4-----------------------------------------------------------------------

select DISTINCT A.title
from Movie A, Keywords B
where A.title=B.title and  B.keyword like '%war%' and A.genre='Action' and not exists 
(select * from Keywords where keyword like '%star%' and title=A.title)
 --------------------------------------Q5------------------------------------------------------------------
 select A.songID, A.[rank]
 from Soundtrack A,Keywords B
 where A.title=B.title and (B.keyword like 'computer' or B.keyword='computer-animation')
 ORDER BY A.[rank]

 ---------------------------------------Q6----------------------------------------------------------------------------------------
 select B.fname,B.lname
 from Actors A , TechStaff B 
 where A.fname=B.fname and A.lname=B.lname

 ----------------------------------------Q7------------------------------------------------------------------------------------------
select D.studioName,Avg(A.salary) as StudioAvgSalary, Avg(E.salary) as TechStaffSalary
from Actors A, ActedIn B, Movie C ,Studio D, TechStaff E
where A.name=B.name and B.title=C.title and C.studioID=D.studioID and E.studioID=D.studioID
group by D.studioName



------------------------------------END OF ASSIGNMENT---------------------------------------------------------------------------

