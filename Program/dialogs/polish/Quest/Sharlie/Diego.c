// Диего де Монтойя
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
			dialog.text = "Czy czegoś chcesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", Szef patrolu San Jose. Otrzymaliśmy wiadomość dotyczącą podejrzanego zachowania na obrzeżach miasta. Czy byłbyś tak uprzejmy i wyjaśnił nam, kim jesteś i co planujesz?";
			link.l1 = "Kapitan "+GetFullName(pchar)+", señor oficerze. Jestem tutaj na mocy autorytetu i bezpośrednich instrukcji Ojca Inkwizytora Vincento. Oto dokument potwierdzający moje uprawnienia.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Dobrze... Wszystko wygląda w porządku. Jest wypełnione poprawnie z podpisem inkwizytora. Przepraszam za moje podejrzenia. Co robisz przy latarni morskiej?";
			link.l1 = "Nie jestem upoważniony do odpowiadania na takie pytania. Jeśli naprawdę interesuje cię cel mojej pracy dla inkwizytora, polecam skontaktować się bezpośrednio z nim w Santiago, aby uzyskać wyjaśnienia. Jesteś oficerem, z pewnością masz wiedzę o tajemnicach wojskowych i służbowych. Jedyne, co mogę ci powiedzieć, to że badam okoliczności wraku hiszpańskiego statku.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Przepraszam, Monsieur. Nie śmiałbym cię dłużej zatrzymywać... ah, jeden moment! Czy właśnie zobaczyłem ostrze zimnej stali, czy to tylko moja wyobraźnia? Co za interesujący sztylet! Czy możesz mi go pokazać?";
			link.l1 = "Upewnij się, że nie zapomnisz mi go oddać. To dla mnie bardzo ważne.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dios mio! Znam ten sztylet, widziałem go w jednej z książek bibliotecznych! To jest sztylet samego Cortésa! Jest tu wyraźnie oznakowany... Monsieur, proszę, nie odmawiaj. Pozwól mi zachować ten sztylet! Zbieram starożytną i spersonalizowaną broń, a to jest po prostu niezwykły okaz. Dobrze za niego zapłacę.";
			link.l1 = "Señor, ten sztylet nie jest na sprzedaż. Dostałem go w prezencie i nie zamierzam go nikomu sprzedawać. Oddaj go, proszę.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Nie będziesz nawet szczęśliwy z pięciuset złotymi dublonami? To przecież kupa pieniędzy. Mógłbyś za nie kupić statek!";
			link.l1 = "Nie. Już mam statek, a ten sztylet jest jedyny w swoim rodzaju. Nie sprzedam go.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, to szkoda... Dobrze, weź swoją cenną rzecz. Nie odważę się już ci przeszkadzać. Powodzenia!";
			link.l1 = "Wszystkiego najlepszego, oficerze.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Dość! Chcę z nim porozmawiać...";
			link.l1 = "Widzę więc samego Diego de Montoya tuż przede mną... Ale wybacz mi, señor. Spotkaliśmy się wcześniej, prawda? Och tak, to prawda. Trynidad, przy miejscowej latarni morskiej. Ale jestem pewny, że tam przedstawiłeś się jakoś inaczej...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Twoja pamięć Ci dobrze służy, sir. Cóż, nie jesteś jedynym, kto potrafi wzniecać intrygi i toczyć wojny za kulisami. Jestem dobrze poinformowany o twoim niezachwianym pragnieniu, by mnie zobaczyć. No cóż, wygląda na to, że twoje życzenie się spełniło.";
			link.l1 = "To nie było dokładnie to spotkanie, na które liczyłem, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "No cóż, jest jak jest. Ale dam ci szansę wyjść stąd żywym, jeśli oddasz mi swój sztylet.";
			link.l1 = "Czy twoja pasja do zbierania rzadkości naprawdę zaprowadziła cię tak daleko, caballero, że musiałeś przygotować tak przemyślaną pułapkę na mnie?  Och, nie sądzę.  Strażnik Prawdy cię prowadzi, czy jestem od tej prawdy daleko?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Nie mam pojęcia, o czym ty mówisz. Sztylet musi wrócić tam, gdzie jego miejsce, i to wszystko, co musisz wiedzieć. Nie chciałeś go oddać za złoto, więc teraz oddasz go za własne życie.";
			link.l1 = "Czy naprawdę sądzisz, señor, że uwierzę w to, co mi właśnie powiedziałeś? Już postanowiłeś, że nie opuszczę tej zatoki, prawda?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "A co jeśli dam ci moje słowo?";
			link.l1 = "Słowo na 'żabojada'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, daję ci ostatnią szansę. Albo oddasz mi sztylet, który mnie interesuje, albo za kilka minut ograbię twoje martwe ciało. Opór jest daremny, mamy przytłaczającą przewagę liczebną.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Zaskoczyłeś mnie, señor, to pewne. Czy naprawdę myślisz, że jestem takim upartym kretynem, że po prostu wsadzę głowę w paszczę rekina, nie trudząc się, by chwycić za swój harpun? Chłopcy, zabić ich!";
			else link.l1 = "Prawdziwa siła nie tkwi w liczbach, lecz w umiejętnościach, señor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
