//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Jó napot, "+GetAddress_Form(NPChar)+". Tisztában vagyok vele, hogy ön a saját hajójának kapitánya. Van egy ajánlatom a számodra.";
					link.l1 = "Figyelek, "+GetAddress_FormToNPC(NPChar)+". Miféle üzlet?";
					link.l1.go = "crew";
					link.l2 = "Elnézést, "+GetAddress_FormToNPC(NPChar)+", de sietek.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hé, kapitány! Mit akarsz egy egyszerû tengerésztôl?","Jó napot, uram. Miben segíthetek?","Jó napot, uram. Szeretne valamit?");
				link.l1 = "Örülök, hogy találkoztunk, haver! A nevem "+GetFullName(pchar)+". Van egy perced beszélgetni?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Szükségem lenne néhány információra errôl a kolóniáról.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Csak köszönni akartam. Viszlát!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Már megint ön, uram? Mit akar még?";
				link.l1 = "Van egy perce beszélgetni?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Szükségem lenne néhány információra errôl a kolóniáról.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Nem, haver, semmiség. Sok szerencsét!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" szolgálatára, jó uram! Mit akar tudni?", 
				"Örülök, hogy beszélhetek önnel, kapitány!", 
				"Nos... Azt hiszem, még van egy kis idôm beszélgetni...",
                "Sajnos, most mennem kell. Viszontlátásra!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Van valami érdekes mondanivalód?", 
				"Van valami érdekes mondanivalód?",
                "Van valami érdekes mondanivalód?", 
				"Persze. Sok szerencsét!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Engem és a társaimat különbözô betegségek és sérülések miatt a partra tettek az utolsó hajónkról. De most már mindannyian egészségesek vagyunk, és szeretnénk újra tengerészként dolgozni. Szeretne felvenni minket?"; break;
				case 1: sTemp = "Engem és néhány társamat egy kereskedelmi hajóról fizettek ki, mert lejárt a szerzôdése. Már régóta nyolc darab pesó nélkül vagyunk, ezért szeretnénk újra munkába állni. Szüksége van néhány ügyes matrózra a legénységébe?"; break;
				case 2: sTemp = "Én és a haverjaim most jöttünk vissza egy két héttel ezelôtti útról. A hajóparancsnok elbocsátott minket, és mi nagyon jól éreztük magunkat. De a zsebünk most üres, úgyhogy ideje újra vitorlát bontani. Fel akar bérelni minket, kapitány?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Nos, kész vagyok megvitatni az ajánlatát. Hányan vagytok és miben vagytok jók?";
			link.l1.go = "crew_1";
			link.l2 = "Sajnálom, matróz, de már így is van elég emberem. Találnia kellene magának egy másik kapitányt.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "Mi vagyunk a legjobbak a vitorlákkal és a vitorlák kezelésében. Nem akarok túlságosan szerénykedni, de azt mondanám, hogy a hajókezelésben profik vagyunk, úgyhogy ne aggódjon, még a legerôsebb viharban sem hagyjuk cserben."; break;
				case 1: sTemp = "Leginkább szeretünk az ágyúfedélzeten lenni. Kevesen közülünk még igazi hadihajón is szolgáltak. Úgy tudunk ágyúkat tölteni és tüzelni, ahogyan a legénységedbôl senki sem tud. Minden kemény harcban számíthatsz ránk!"; break;
				case 2: sTemp = "Jó hajósok vagyunk, kapitány, voltunk már párszor magánhajókon is. Ismerjük a bicskák csillogását, a puskapor és a vér szagát. Ez a mi hivatásunk. Nem könnyû legyôzni minket közelharcban, így mindig számíthat a pengéinkre, kapitány!"; break;
			}
			dialog.text = "A "+sti(npchar.quest.crew.qty)+" vagyunk, és csak együtt fogunk bérelni. Minden alapvetô hajós feladatot el tudunk végezni."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Úgy hangzik, mint akiket keresek. Mi a helyzet az elômeneteleddel?";
				link.l1.go = "crew_2";
				link.l2 = "Sajnálom, matróz, de jelenleg más képességekre van szükségem. Találj magadnak egy másik kapitányt.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Sajnálom, matróz, de nincs elég hely a hajómon. Találjon magának egy másik kapitányt.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" Mindenkinek. Aztán a szokásos matrózbér havonta. Nem kérünk túl sokat, kapitány.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Fel vagy véve! Fogd az érméket. Most menj a hajómhoz, a neve '"+pchar.ship.name+"', pont a kikötôben. A hajóskapitány kiosztja nektek az összes függôágyat a legénységi szálláson, és megkapjátok az étkezést.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Sajnos nem engedhetem meg magamnak, hogy mindannyiótoknak fizessek. Találnotok kellene magatoknak egy másik kapitányt.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Igenis, kapitány! Összeszedem a legénységet, és azonnal indulunk.";
			link.l1 = "Siessetek, egy pillanat alatt indulunk.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Matrózok", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Ágyúk", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Katonák", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Hé, tedd a kardodat a hüvelybe, kapitány. Egyikünknek sincs szüksége problémákra, igaz?", "Hé, tedd le a kardodat, sapka. Egyikünknek sincs szüksége problémákra, igaz?");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Ahogy mondod.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
