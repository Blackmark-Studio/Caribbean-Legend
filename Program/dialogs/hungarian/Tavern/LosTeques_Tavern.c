#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("A városban riasztást adtak ki. Mindenki téged keres! Én a helyedben nem várnék itt túl sokáig.", "Az egész ôrség átfésüli a várost, hogy megtalálja magát. Nem vagyok hülye, és nem fogok veled beszélni!", "Fuss, pajtás, mielôtt a katonák fasírtot csinálnak belôled..."),
					LinkRandPhrase("Mit akarsz, gazember?! A városôrség már a nyomodban van. Nem jutsz messzire, kalóz!", "Mocskos gyilkos, takarodj a házamból! Ôrség!", "Nem félek tôled, kutya! Hív a hurok, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, nem aggódom a riasztó miatt...", "Nincs esélyük elkapni engem."),
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kivágom az istenverte nyelvedet.", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", te is kalózra akarsz vadászni? Figyelj, haver, maradj nyugodt, és talán túléled..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! Üdvözöljük, " + GetAddress_Form(NPChar) + " a Los-Teques bányakocsmában. Ételek, italok és lányok, mindezt megfizethetô áron! A nevem "+GetFullName(npchar)+" és mindig a rendelkezésedre állok.";
				Link.l1 = "Lássuk csak... Én vagyok " + GetFullName(pchar) + ". Örülök, hogy megismerhetem, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, régi ismerôsöm, kapitány "+GetFullName(pchar)+"! Örülök, hogy látlak, öregem! Rumot, lányok?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Önts nekem egy kis rumot, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Szeretnék egy kicsit aludni. Van egy szabad szobájuk?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Van valami aktuális híre?","Mi újság errefelé?","Hogy alakul az élet a szárazföldön?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Nem, nincs szükségem semmire, "+npchar.name+". Csak beugrottam köszönni.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ó, annyira boldog vagyok! Az új arcok ritkaságnak számítanak a városunkban. Mi lenne, ha töltenék egy kis rumot, és beszélgetnénk...";
			link.l1 = "Most vagyok itt elôször, és szeretnék egy kicsit többet megtudni errôl a településrôl.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Önts nekem egy kis rumot, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Szeretnék egy kicsit aludni. Van egy szabad szobájuk?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nincs semmi érdekes mondanivaló. Mindennap ugyanaz: unalom, nap és por. Csak katonák, négerek és indiánok élnek itt. Találkozhatsz néhány kalandorral és aranyra éhes banditákkal is\nNéha urak, hozzád hasonló kapitányok látogatnak el hozzánk, hogy rabszolgákat adjanak el ingókért és nemesfémet vásároljanak. A kereskedônk elég érdekes ember, nemcsak arany- és ezüströgöket, hanem féldrágaköveket is árul\n Azt állítja, hogy a különleges tudással rendelkezô emberek nagyon hasznosnak találhatják ezeket a kavicsokat. Nézzétek meg tehát a boltunkat. Maga a bánya tovább a hegy alatt található. Ha akarod, meglátogathatod, de azt javaslom, hogy ne idegesítsd fel az ôrséget\nNe beszélj elítéltekkel, és Isten óvjon a lopástól. Egyébként a legjobb hely ezen a településen a kocsmám, a legjobb hely, ahol kipihenheted ezt az égô poklot!";
			link.l1 = "Köszönöm az információt!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Kapitány, szerintem jobb, ha megállsz. Isten ments, hogy alkoholos befolyásoltság alatt poklot csináljon. Mi itt nagyon szigorúak vagyunk ezzel kapcsolatban. Még a tekintélye sem segít magán.";
				link.l1 = "Hm... Azt hiszem, igazad van - már eleget ittam. Köszönöm az aggódást!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Szívesen, kapitány. Csak öt darab pesó egy korsó legjobb fekete jamaikai rumomért!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Rendben, az egészségedre és a létesítményed virágzására, pajtás!","Minden jót a tengeren lévôknek!","Minden jót a városod jólétére!"), LinkRandPhrase("Minden jót, a termelés szelére, a szerencse szellôjére, hogy mindannyian könnyedebben és gazdagabban éljünk!","Minden rendben, hogy a szél mindig a hátunkba fújjon minden ügyünkben!","Minden rendben, a boldogságra, a szerencsére, az örömre és a leányokra!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Senor, ön fizetett egy szobáért és egy lányért. Menjen fel az emeletre, már vár magára egy ideje.";
				link.l1 = "Rendben van.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Igen, így van. Meddig akartál maradni?";
			if(!isDay())
			{
				link.l1 = "Reggelig.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Éjszakáig.";
				link.l1.go = "room_night";
				link.l2 = "Másnap reggelig.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Az tíz darab nyolc darab lesz. Szeretne egy lányt is a szobába mellé? Csak ezer pezó a lányért.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nem, nincs szükségem lányra. Tessék, fogd ezt a szobáért.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Igen, a szobát és a lányt is elfogadom. Itt a pénz.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Sajnos, nem engedhetem meg magamnak a szobát.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Az tíz darab nyolc darab lesz. Szeretne egy lányt is a szobába mellé? Csak ezer pezó a lányért.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nem, nincs szükségem lányra. Tessék, fogd ezt a szobáért.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Rendben. Vegyük a szobát és a lányt. Itt a pénz.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Sajnos, nem engedhetem meg magamnak a szobát.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Az tíz darab nyolc darab lesz. Szeretne egy lányt is a szobába mellé? Csak ezer pezó a lányért.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nem, nincs szükségem lányra. Tessék, fogd ezt a szobáért.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Rendben. Vegyük a szobát és a lányt. Itt a pénz.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Sajnos, nem engedhetem meg magamnak a szobát.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Menjen fel, senor. A lány már várja önt. Kellemes pihenést!";
			link.l1 = "Köszönöm, haver...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Hogyan, fehér mester. Ne nézz így "+npchar.name+" , "+npchar.name+" mindent jobban tud, mint a fehér squaw a kuplerájból. Ah, senor, te olyan jóképû vagy... Ígérem, ez a squaw sokáig fog szeretni téged.";
			link.l1 = "Ez jól hangzik, mutasd meg a legjobb indiai bájaidat. Nem kell az esôtánc, hogy eláztassalak...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás fényes nappal!!!! Mi folyik itt?! Várj, várj, haver...", "Hé, mit csinálsz ott?! Ki akarsz rabolni? Most aztán jól elbasztad...", "Várj, mi a fenét csinálsz? Kiderült, hogy tolvaj vagy! Vedd úgy, hogy itt a vége, seggfej...");
			link.l1 = LinkRandPhrase("Ördög!", "Bassza meg!", "Ah, a francba");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
