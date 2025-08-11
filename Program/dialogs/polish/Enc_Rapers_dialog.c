void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Idź swoją własną drogą, "+GetSexPhrase("kolego","dziewczyno")+". Kobitka ostatecznie nam podziękuje, wiesz.","Spływaj! Pozwól panom się zabawić.","To nie twoja sprawa, "+GetSexPhrase("nieznajomy","dziewczyno")+". Będziemy się tylko bawić, i to wszystko!");
				link.l1 = LinkRandPhrase("Nie pozwolę na to!","Porzuć swoje złe plany natychmiast!","Nie będe tolerować żadnej przemocy!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Rozumiem, już odchodze. Przepraszam za kłopot.","Nie ośmielę się już ci więcej przeszkadzać. Przepraszam, że ci przeszkodziłem.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Idź swoją drogą, "+GetSexPhrase("koleżko","dziewczyno")+". Ona nam na końcu podziękuje, wiesz.","Spływaj! Pozwól panom się zabawić.","To nie twoja sprawa, "+GetSexPhrase("nieznajomy","dziewczyno")+". Będziemy się tylko bawić, i to wszystko!!");
					link.l1 = LinkRandPhrase("Nie pozwolę na to!","Porzuć swoje złe plany natychmiast!","Nie będę tolerować żadnej przemocy!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Rozumiem, odchodzę. Przepraszam za kłopot.","Nie ośmielę się już ci więcej przeszkadzać. Przepraszam za kłopot.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hej, "+GetSexPhrase("obcy","młoda damo")+", dlaczego szukasz kłopotów? Ta dziewczyna jest 'znaną' osobą w naszej osadzie. Już jej zapłaciliśmy, ale zauważyła ciebie i zdecydowała się uciec z naszymi pieniędzmi.","Hej, "+GetSexPhrase("kolego","dziewczyno")+", idź swoją drogą i nie wtrącaj się w nasze sprawy. Wygraliśmy tę dziewczynę w grę w kości, ale była trochę zbyt szybka, więc uciekła, goniliśmy ją przez godzinę w tej dżungli.");
					link.l1 = "Nie obchodzi mnie to, nie pozwolę ci jej skrzywdzić!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Och, rozumiem! I prawie jej uwierzyłem! Taka niewiasta...","A, cóż, to już inna sprawa. Bawcie się dobrze, chłopaki!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Idź swoją drogą, "+GetSexPhrase("dobry człowieku","młoda damo")+". Poradzimy sobie bez ciebie.";
					link.l1 = "Nie będę tolerować żadnej przemocy!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hej, "+GetSexPhrase("nieznajomy","młoda dama")+", dlaczego szukasz kłopotów? Ta dziewczyna jest 'znaną' osobą w naszej osadzie. Już jej zapłaciliśmy, ale zauważyła ciebie i postanowiła uciec z naszymi pieniędzmi.","Hej, "+GetSexPhrase("kolego","dziewczyno")+", idź swoją drogą i nie wtrącaj się w nasze sprawy. Wygraliśmy tę dziewczynę w kości, ale była trochę zbyt szybka, by uciec, goniśmy ją już godzinę.");
					link.l1 = "Nie obchodzi mnie to - nie pozwolę ci jej skrzywdzić!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("O, rozumiem! I prawie jej uwierzyłem! Taka kocica...","Ach, cóż, to już inna sprawa. Bawcie się dobrze, chłopaki!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Cóż, na pewno wybrałeś nieodpowiedni czas na spacer...","Czyli, zdecydowałaś się być bohaterem?")+"Zajmijmy się "+GetSexPhrase("nim","nią")+", chłopaki!","Ty "+GetSexPhrase("gnoju","szmato")+"! Ośmielasz się stanąć nam na drodze?! Już ja ci pokaże, "+GetSexPhrase("chłystku","cwaniaro")+"!");
			link.l1 = "Widziałem bardziej groźnych ludzi!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Powinieneś wiedzieć, że ona nas dużo kosztowała! A jeśli jesteś tak szlachetny, możesz ją wziąć za "+sti(pchar.GenQuest.EncGirl.price)+" pesos."+GetSexPhrase(" Dobrze się z nią zabawisz, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Tu są twoje pieniądze. Biorę ją ze sobą.","Przestań szczerzyć zęby. Zabieram dziewczynę ze sobą. Tu masz swoje pieniądze.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Czyli chcesz pieniędzy? A co powiesz na zimną stal?","To ma być zabawne? Popatrz na dziewczynę, wariacie! Ona się boi!","Komu próbujesz wciskać kit, ty degeneracie!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Dlaczego jej w ogóle wierzysz? Jaka przemoc? Uciekła z domu, a my zostaliśmy wysłani przez naszego szefa, aby ją znaleźć.";
			link.l1 = RandPhraseSimple("No cóż, to już inna historia. Idź gonić za swoim uciekinierem.","Ach, rozumiem. W takim razie goń za nią dalej... ja mam trochę spraw do załatwienia.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Takie bajeczki to swoim wnukom możesz poopowiadać, jeśli dożyjesz, by je mieć!","Komu próbujesz wcisnąć kit, ty łajdaku?!");
			link.l2.go = "Node_6";
			link.l3 = "Sam ją zaprowadzę do domu, aby uniknąć czegoś złego. Kim są jej rodzice?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Chcesz umrzeć? To twój wybór...";
			link.l1 = "Patrz kto mówi.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "jest kupcem";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "nadzoruje lokalnym portem";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "służy jako więzienny komendant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "to właściciel stoczni";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Jej ojciec "+pchar.GenQuest.EncGirl.FatherNom+", w osadzie "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". Ale proszę, nie zawiedź nas, bo on to nie jest kimś, z kim można się zadzierać, on nas wszystkich obedrze ze skóry...";
			link.l1 = "Nie martw się. Dostarczę ją do niego.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "Znowu się spotykamy. Gdzie jest twoja towarzyszka? Ach, w zasadzie nie potrzebuję jej, jeśli ty jesteś tutaj.";
			link.l1 = "Panowie, naprawdę myślę, że już otrzymaliście wystarczająco dużo pieniędzy, aby zostawić tę dziewczynę w spokoju.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "noge";
				break;
				case 1:
					sTemp = "ręke";
				break;
				case 2:
					sTemp = "ucho";
				break;
				case 3:
					sTemp = "nos";
				break;
				case 4:
					sTemp = "oko";
				break;
			}
			dialog.text = "Co te twoje pieniądze znaczą w porównaniu do skarbów "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+". Był takim sknerą, że nie chciał wydać za mąż własnej córki, bo chciał uniknąć dodatkowych wydatków... \nOn naszą część w swoich skrzyniach! ."+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" stracił podczas abordażu "+sTemp+"! I co zamiast tego ma? "+"Żałosną garść srebra? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" zawsze zabierał cały łup do swojej kryjówki. I teraz nie zamierzamy się poddawać! Pokaż nam, gdzie są jego skrzynie!";
			link.l1 = "Cóż, na pewno nie zgłosiłem się do strzeżenia skarbów twojego kapitana, ale nie mogę ci pokazać miejsca... Ponieważ nie wiem, gdzie to miejsce jest.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Kłamiesz!!! Czuję zapach złota wydobywający się z tej jaskini! Pokaż mi to miejsce, jeśli nie chcesz umrzeć!";
			link.l1 = "Widzę, że moje słowa nie przekonały cię. Może mój sztylet będzie bardziej wyrazisty?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Ty "+GetSexPhrase("szczeniaku","latawico")+"! Z drogi!";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Witaj, dobr"+GetSexPhrase("y panie","a pani")+". Mamy na ciebie skargi.";
			link.l1 = "Skargi od kogo? Od tej kurwy?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Pilnuj swojego języka, dobrze? Nie pozwolę ci obrażać mojej siostry! Najpierw ją molestowałeś w dżungli, a potem przyprowadziłeś ją tutaj "+GetSexPhrase("na więcej nieprzyzwoitości","i obrabowałaś")+".";
			link.l1 = "Hej kolego, naprawdę muszę tego wszystkiego słuchać?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Nie. Skromna suma zaledwie "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" pesos uratuje cię od wszelkich kłopotów.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Cóż, szlachetne czyny na pewno są trochę kosztowne w dzisiejszych czasach. Dobrze, weź to...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Myślę, że byłoby taniej zrobić dziurę w twoim brzuchu, abyś nie stał mi na drodze do wyjścia.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Nie. Ale również wywrócisz kieszenie na lewą stronę, inaczej cię dźgnę!";
				link.l1 = "Dobrze, bierz to, łotrzyku! Ale nie ujdzie ci to na sucho...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Myslę, że łatwiej byłoby zrobić dziurę w twoim brzuchu, abyś nie stał mi na drodze do wyjścia.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Bardzo dobrze. Dobrze, że się pozbyliśmy tego problemu.";
			link.l1 = "Wypad.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Oczywiście, że nie, oczywiście... No, do widzenia, "+GetSexPhrase("panu","pani")+". "+GetSexPhrase(" I pamiętaj, nie jesteś tak przystojny, żeby każda dziewczyna od razu za tobą poszła. To była by moja lekcja dla ciebie.","")+"";
			link.l1 = ""+GetSexPhrase("To na pewno!..","Znikaj już!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Wyglądasz jak "+GetSexPhrase("szlachetny człowiek","dobrze wychowana dama")+", dlaczego takie groźby?";
			link.l1 = "To mi najbardziej pasuje...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "No cóż, sam o to prosiłeś! Czy powinniśmy "+GetSexPhrase("go połaskotać","ją połaskotać")+" naszą stalą, chłopcy?";
			Link.l1 = "Modl się, zanim umrzesz!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Chcesz do nas dołączyć, czy jak? "+GetSexPhrase("Spływaj, dla nas wszystkich nie starczy","Spływaj, póki możesz, jedna dziewczyna nam wystarczy")+"!";
			Link.l1 = "Cóż, w takim razie nie będę ci przeszkadzał.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Nie pozwolę na żadną przemoc!";
			Link.l2.go = "Node_2";
		break;				
	}
}
