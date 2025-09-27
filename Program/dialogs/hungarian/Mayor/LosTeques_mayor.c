void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Ide merészelsz jönni?! Merész lépés...", "Hogy engedhették meg ezek a hülyék, hogy egy ellenség betörjön?! Nem értem...", "Nos, az ôreimnek semmi haszna, ha valami idióta járkál a rezidenciámban..."), 
					LinkRandPhrase("Mit akarsz, te szemétláda?! A katonáim már a nyomodban vannak, és nem fogsz elmenekülni"+ GetSexPhrase(", mocskos kalóz"," mocskos kalóz") +"!", "mocskos gyilkos, tûnj el a rezidenciámról! Ôrség!!!", "Nem félek tôled, fattyú! Felakasztalak, nem úszod meg..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("A katonák nem kerülnek semmibe...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy levágom a tüdôdet és a torkodba dugom...", "Én azt mondanám neked, haver: ülj csendben, és talán még megélsz egy újabb napot..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Ellenség a rezidenciámban! Riadó!";
				link.l1 = "Basszus!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + " Uram. A nevem "+GetFullName(npchar)+", a Lost-Tekes bánya parancsnoka, amely a " + NationKingsName(npchar)+"tulajdonában van. Lenne szíves elmondani látogatásának célját, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "Elôször vagyok itt, és szeretnék többet megtudni errôl a településrôl és a törvényeirôl...";
				link.l1.go = "info";
				link.l2 = "Csak üdvözölni akartam, máris indulok.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Már megint ön, uram? Mit akar még?";
			link.l1 = "Semmit. Elmegyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Tisztelem az ilyen fegyelmet. Nos, ebben az esetben tájékoztatom, ha már ennyire érdekli.\nLos-Teques bánya a spanyol korona tulajdona. Ezüst és arany nyers ércet bányászunk itt, valamint ezüst és arany rögöket. Minden arany és ezüst Spanyolország tulajdona, és az Óvilágba szállítják.\nA bánya jól ôrzött, mindig állomásozik itt egy spanyol elit katonákból álló egység. A kalózok többször is megpróbálták kirabolni a bányát, de a következmények mindig rosszul jártak... számukra.\nAmint látod, ez egy kisváros. Van egy kocsmánk és egy boltunk. Ott jó áron lehet arany- és ezüstrudakat vásárolni. Emellett a szállásmesterünk, aki egyben kereskedô is a boltban, más érdekes fémeket és érceket is eladhat neked.\nA legtöbb munkásunk elítélt, de van egy kis fekete rabszolgánk is. Mint látod, mindig szükségünk van új munkaerôre, minden nap meghal legalább egy ilyen átkozott elítélt.\nSzóval, ha hozol nekünk rabszolgákat, rögöket cserélünk értük. Ilyen ügyekben forduljon a vezetô mérnökünkhöz. Ôt az aknában találjátok.\nViselkedjetek itt. Ne kezdjetek párbajokat vagy verekedéseket, ne próbáljatok meg ellopni semmit, különösen aranyat vagy ezüstöt. Itt nincs börtönünk, de van hadbíróságunk.\nEz nagyjából ennyi. Kövesd ezeket az egyszerû szabályokat, és nem lesz gondod. Szabadon mozoghatsz a bányában. Ne felejtsétek el meglátogatni a kocsmát, ôk bizonyos... szolgáltatásokat végeznek az engedélyemmel. Üdvözöllek benneteket!";
			link.l1 = "Köszönöm!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Rablás!!! Ez elfogadhatatlan! Készülj fel, "+ GetSexPhrase("haver","lány") +"...";
			link.l1 = LinkRandPhrase("A francba!", "Carramba!!", "A francba!");
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
