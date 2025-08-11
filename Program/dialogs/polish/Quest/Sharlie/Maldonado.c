// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy czegoś potrzebujesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Stój, Kapitanie "+GetFullName(pchar)+"...";
			link.l1 = "Jakoś nie dziwi mnie obecność hiszpańskich żołnierzy tutaj... Chyba już się przyzwyczaiłem, że zawsze ktoś depcze mi po piętach. Czego szukasz na tej zapomnianej przez Boga wyspie, Kastylijczyku? Szukasz szybkiego sposobu na odłożenie nóg do góry?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Jestem Alonso de Maldonado. To może ci nic nie mówić, ale Diego de Montoya może wydać się znajomy. Był moim najlepszym przyjacielem. Ocalił mi życie, a teraz jego krew jest na twoich rękach.";
			link.l1 = "Domyślam się, że podążałeś za mną, by szukać zemsty?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Nie szukam tylko zemsty. Z tego co rozumiem, masz maskę Kukulkana?";
			link.l1 = "Cholera jasna! Kolejny poszukiwacz skarbów! Przybywasz, by dokończyć sprawy rozpoczęte przez Don Diega?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Nie interesują mnie skarby. Widziałem bogactwa w Tayasal. Miguel Dichoso nie zdołał wywieźć więcej niż okruszek. Maska jest tym, czego pragnę.";
			link.l1 = "Byłeś w Tayasal? Trudno w to uwierzyć. Z tego co pamiętam, Dichoso był jedynym ocalałym z ekspedycji.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Udałem się do Tayasal dwadzieścia lat przed tym, jak Dichoso tam dotarł. W tym samym czasie szalony czarownik Kanek użył tego nikczemnego rytuału ofiary z ludzi, by ukryć maskę na tej wyspie.";
			link.l1 = "Nie mogę uwierzyć w to, co słyszę! Jesteś z tej samej bandy konkwistadorów, która została tam przywieziona, by zostać złożona w ofierze, gdy Strażnik Prawdy był tworzony? Wszyscy jesteście martwi!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Nie wszyscy z nas. Ja przetrwałem.";
			link.l1 = "Dlaczego Itza postanowili cię oszczędzić? Co czyni cię tak wyjątkowym?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Nie zrozumiałbyś tego. Do diabła, ja też tego nie rozumiałem. Nikt mnie nie oszczędził. Pamiętam to, jakby to było wczoraj... Zaraz po tym, jak ten dzikus wziął sztylet i odciął kawał skóry z pleców Casco, zanim go zabił i zaczął wyć jak szaleniec, myślę, że zostałem wciągnięty do idola. Obudziłem się daleko od Tayasal dwadzieścia lat później, co wydawało się zaledwie chwilą!";
			link.l1 = "Lejek czasoprzestrzenny... Cholera jasna, wszystko co Ksatl Cha powiedział, było w punkt! Skąd dowiedziałeś się o masce? Do czego jej potrzebujesz?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Muszę powstrzymać pomiot piekielny, przyzwany przez szalonego indiańskiego czarownika. Ta ohyda zamierza rozpalić stos z naszego świata!";
			link.l1 = "Hmm... Rozmawiałeś z ojcem Vincento, prawda? Inkwizytor trzyma zająca i goni z chartami. Niespodzianka, niespodzianka. Wysłał cię, by mnie wytropić na bitwę królewską? Dobra robota! Wykonałeś swoją misję, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "Pan umacnia moją dłoń w walce przeciwko złu. Powrócę do Tayasal i użyję maski, aby na zawsze zamknąć bramy. I żaden demon w ludzkiej formie nigdy nie przekroczy do naszego świata.";
			link.l1 = "Jest tylko jeden mały problem w twoim planie, Don Alonso. Demon JUŻ jest wśród nas. Wszystko, co musimy zrobić, to nie pozwolić mu OPUŚCIĆ tych bram. Nie będzie w stanie tego zrobić, dopóki będziesz trzymać maskę z dala od niego.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "To będzie wymagało czegoś więcej, niż trzymania maski z daleka od tego demona. Niezależnie, kto z nas ma rację, jedno jest pewne: bramy muszą być zamknięte na zawsze. I jest tylko jeden sposób, by to zrobić: zniszczyć maskę na ołtarzu Tayasal. Dzięki temu demon zostanie pozbawiony całej swojej mocy.";
			link.l1 = "Hm. Zgadzam się, że to nasza najlepsza szansa... Jak planujesz dostać się do Tayasal? Znasz drogę?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Łatwa ścieżka, którą używaliśmy wtedy, już nie istnieje. Drogi są zasypane kamieniami i zagubione w dżunglach. Istnieje inna droga do miasta, ale jest długa i niebezpieczna. Ścieżka zaczyna się na najbardziej północnej zatoce Jukatanu. \nZ pomocą ojca Vincenta i don Ramona de Mendozy zbiorę oddział elitarnych żołnierzy i przejdziemy przez selwę chronioną przez dzikusów Itza. Nie będzie łatwo, ale Bóg obdarzy nas siłą i odwagą w naszej walce w imię naszej wiary.";
			link.l1 = "Don Alonso, moje aspiracje przypadkiem pokrywają się z twoimi. Czyż nie nadszedł czas, by na chwilę odłożyć urazy na bok i połączyć siły? Razem będziemy mieli większą szansę na pomyślne zakończenie tej krucjaty.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Jestem hiszpańskim żołnierzem. Nie zawieram sojuszy z heretykami ani nie robię interesów z Francuzami. Poza tym, już ogłosiłem moją vendettę na ciebie za Don Diego. Życie za życie!";
			link.l1 = "Jesteś uparty jak osioł, Don Alonso! Stoisz tutaj, głosząc, że światu grozi wielkie zło, a jednak odmawiasz mojej pomocy w wykonaniu tak astronomicznego zadania!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Teraz to ja podejmuję decyzje, a nie ojciec Vincento! Odmawiaj modlitwy i szykuj się na śmierć, francuski kapitanie!..";
			link.l1 = "Och, słyszałem to już tyle razy w ciągu ostatnich kilku miesięcy! En garde, twardogłowy caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
