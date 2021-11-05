from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import UserCreationForm
from django.shortcuts import render, redirect
from django.views import View

from home.forms import UserRegistrationForm
from home.models import Jedi


@login_required()
def home(request):
    context = {
        'jedis': Jedi.objects.all(),
    }
    return render(request, 'home/index.html', context=context)


class RegisterView(View):
    def get(self, request):
        form = UserRegistrationForm()
        return render(request, 'home/register.html', context={'form': form})

    def post(self, request):
        form = UserCreationForm(request.POST)
        if form.is_valid():
            user = form.save()
            return redirect('/login')
        else:
            return render(request, 'home/login.html', context={'form': form})
