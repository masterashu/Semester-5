from django.db import models
from django.contrib.auth.models import AbstractUser


class UserInfo10017(AbstractUser):
    dob = models.DateField()
    REQUIRED_FIELDS = ['email', 'dob', ]


class ForceUser(models.Model):
    pass


class Jedi(ForceUser):
    GENDER = (('M', "Male"), ('F', "Female"), ('A', "Alien"))
    LIGHTSABER_COLOR = (('P', "Purple"), ('B', "Blue"), ('G', "Green"), ('Y', "Yellow"), ('N', "None"))
    JEDI_POSITION = (
        ('Y', "Youngling"), ('P', "Padawan"), ('K', "Knight"), ('M', 'Master'), ('W', "Warrior"), ('S', "Sage Master"),
        ('J', "Jedi Master"),
    )

    name = models.CharField(max_length=180)
    age = models.IntegerField(default=0)
    gender = models.CharField(choices=GENDER, max_length=1)
    is_force_ghost = models.BooleanField(default=False)
    lightsaber_color = models.CharField(choices=LIGHTSABER_COLOR, max_length=1)
    power_level = models.IntegerField(default=1)
    jedi_position = models.CharField(choices=JEDI_POSITION, max_length=1)

    def __str__(self):
        return self.name
