void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Mówią, że wczoraj w tawernie była bójka... Ale kto się bił - diabli wiedzą. Moja gęba cała. Chyba.";
				link.l1 = "Wygląda na to, że była tu niezła popijawa?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Hej, "+GetSexPhrase("chłopie","koleżanko")+", nie widział"+GetSexPhrase("eś","aś")+" mojego buta? Ktoś go ukradł, gdy spałem pijany pod stołem w tawernie.";
						link.l1 = "Pilnuj się, bo zaraz stracisz i drugi.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Mówią, że wczoraj w karczmie była bójka... Ale kto się bił – nikt nie wie. Moja gęba jest cała. Chyba.";
						link.l1 = "Widocznie uznali, że twoja twarz już wystarczająco oberwała.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Na wszystkie diabły, wczoraj miałem sakiewkę ze złotem! Gdzie ona się podziała?!";
						link.l1 = "Dla prawdziwego pirata złoto nie jest najważniejsze. Wolność ma większą wartość.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "I to jaka! Karczmarz miał pełne ręce roboty... hik... A jeszcze... ktoś ukradł mu gin! Nie butelkę, ale całą beczkę! I to taką, jakiej nie znajdziesz w całych Karaibach! Mówią, że sprowadzona aż z Europy. Dla kogo ją trzymał — nie mówi, ale jedno jest pewne: jeśli szybko jej nie znajdą, biedaka czeka piekielna burza!";
			link.l1 = "Ciekawe. Trzymaj się, pijaku.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Czego jeszcze chcesz? Nie widzisz, że głowa mi pęka? Odczep się.";
					link.l1 = "Mniej pij, może wtedy zaczniesz wyglądać jak człowiek.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Zostaw mnie... Głowa mi zaraz eksploduje!";
					link.l1 = "Zadziwiające, że jeszcze trzyma się na karku.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Do diabła z tobą... Zostaw mnie w spokoju, nie widzisz, że nie mam teraz do tego głowy?!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Zostaw mnie w spokoju! Nie widzisz, że jestem na skraju?! Ręce mnie aż świerzbią, żeby komuś przywalić.";
			link.l1 = "Spokojnie, kolego. Chcę tylko wiedzieć, co się wczoraj działo w karczmie.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Karamba! Co ty, "+GetSexPhrase("kolejny kochanek","krewna")+" tej szalonej kelnerki? Czego chcesz – żeby cię wichura porwała? Wyzwiesz mnie na pojedynek? Czy od razu wyciągniesz szablę?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Krewna? Wątpię. Ale wygląda na to, że nie masz o niej zbyt wysokiego mniemania?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Kochanek? Mało prawdopodobne. Wygląda na to, że dziewczyna stawia raczej na ilość niż jakość, co?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Nie interesują mnie jej przygody. Powiedz po prostu, co się wydarzyło, i dam ci spokój. To ty ją doprowadziłeś do szału?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;

		case "OS_Matros_3_scrit":
			dialog.text = "Ta furiatka ma chyba gust jak głodny marynarz – bierze, co popadnie! Cały wieczór rzucała spojrzenia i kokietowała jak kot przy kambuzie. Ale jak tylko spróbowałem się zbliżyć – wrzasnęła tak, że ryby w zatoce poszły na dno!";
			link.l1 = "Może po prostu wypiłeś za dużo i byłeś zbyt natarczywy?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "Ta furiatka ma chyba gust jak głodny marynarz – bierze, co popadnie! Cały wieczór rzucała spojrzenia i kokietowała jak kot przy kambuzie. Ale jak tylko spróbowałem się zbliżyć – wrzasnęła tak, że ryby w zatoce poszły na dno!";
			link.l1 = "Może po prostu wypiłeś za dużo i byłeś zbyt natarczywy?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Może i byłem pijany, ale dokładnie pamiętam, co się tam działo. To nie ja na nią polowałem – to ona krążyła wokół mnie jak rekin wokół padliny. Cały dzień nie odstępowała mnie na krok!";
			if (pchar.sex == "woman")
			{
				link.l1 = "I przez taki drobiazg chcesz bić pierwszego lepszego? A może wydarzyło się wtedy coś jeszcze?";
			}
			else
			{
				link.l1 = "Powiedziałeś 'kolejny kochanek'. Wiesz coś o jej innych znajomościach?";
			}
			link.l1.go = "OS_Matros_5";
		break;
		
		case "OS_Matros_5":
			dialog.text = "Jak już przestała wrzeszczeć, moi chłopcy powiedzieli mi, że niepotrzebnie próbowałem zarzucić kotwicę w jej zatoce. Podobno ma jakiegoś adoratora w mieście, który trzyma się z naszym kapitanem.";
			link.l1 = "Zabawne. A nic więcej nie zauważyłeś? Może ktoś podszedł do baru podczas tej kłótni?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Diabli nadali... Głowa mi pęka, a ty jeszcze z tymi pytaniami. Nic nie widziałem i nic nie słyszałem. Lepiej dał"+GetSexPhrase("","a")+"byś parę peso, zamiast dręczyć starego wilka morskiego.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Masz tu sto peso. Tylko się znowu nie nachlej i nie daj się omotać tej kelnerce, heh.";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Obejdzie się. Jeszcze się nachlejesz i znów będziesz się do kelnerki przystawiał.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hej, Jack! Masz tu jakąś portową lafiryndę! Ha-ha! Spójrz tylko na nią – niezła z niej diablica! Ciekawe, czy już przetrząsnęła wszystkie skrzynie, czy może przerwaliśmy jej w najciekawszym momencie?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Hej, Jack! Masz tu szczura! Ha-ha! Spójrz tylko na niego – niezły z niego łotr! Wygląda na to, że już grzebał w naszych skrzyniach, co za spryciarz!";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Odważna panienka. Wpakować się do legowiska Jacka Veilsa – nie każdy by się na to odważył. No i co cię tu sprowadza, maleńka? Przyszłaś nas tu zabawiać?";
				link.l1 = "Zabawiać? Ha! Widzę, że jesteście niezłymi marzycielami, panowie. Przyszłam odebrać to, co ukradliście. Wy naprawdę myśleliście, że ta żałosna szopka ujdzie wam na sucho?";
			}
			else
			{
				dialog.text = "Odważny robaczek. Włamać się do domu Jacka Veilsa – na to trzeba mieć tupet. No i co tu robisz?";
				link.l1 = "Powiedzmy, że oddaję to, co zostało skradzione. Wy naprawdę myśleliście, że ta żałosna inscenizacja nie zostanie odkryta?";
			}
			link.l1.go = "OS_Dialog_4";
		break;
		
		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;
		
		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Żałosna szopka?! Niech mnie piekło pochłonie, zaraz zdejmę z ciebie skórę i zrobię z niej żagiel! Ha-ha! A może najpierw powinniśmy się trochę... pobawić?";
				link.l1 = "Widzę, że aż się palicie, żeby trafić na tamten świat? Dobrze, nie będę was trzymać w niepewności – do broni, parszywe ścierwa!";
			}
			else
			{
				dialog.text = "Żałosna inscenizacja? Niech mnie piekło pochłonie, zaraz zdejmę z ciebie skórę i zrobię z niej żagiel! Dosyć gadania – to twój koniec, ścierwo!";
				link.l1 = "Skoro tak nalegacie – no to do walki, dranie!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;

		case "OS_Dialog_bitva":
			DialogExit();

			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);

			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");

			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;

		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", gdzie jest mój gin?! Jeśli to nie ty go masz, osobiście zatopię cię na dno, byś karmił ryby!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Właśnie go przyniosł"+GetSexPhrase("em","am")+". Proszę bardzo.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("Oddałeś beczkę ginu", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Dobrze, że się na tobie nie zawiodłem, "+sld.name+". Wpadnij jutro – dostaniesz swoje dublony.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Kapitanie, co do tabliczki...";
			link.l1 = "Jakiej tabliczki? A, tej... Cóż, takie zaszczyty to chyba nie dla mnie. Nie trudźcie się, poradzę sobie bez niej.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Mam dla was coś lepszego! Od teraz w mojej tawernie zawsze będzie na was czekać darmowy nocleg i napitek na koszt domu! Człowiek taki jak wy bez wątpienia na to zasługuje!";
			link.l1 = "O, to już co innego! Takie przywileje bardzo mi się podobają! Do zobaczenia, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}