void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
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
					LinkRandPhrase("A városban riasztást adtak ki. Mindenki téged keres! Én a helyedben nem várnék itt túl sokáig.", "Az egész városôrség átfésüli a várost, hogy megtalálja magát. Nem vagyok hülye, és nem fogok veled beszélni!", "Fuss, haver, mielôtt a katonák darált húst csinálnak belôled..."),
					LinkRandPhrase("Mit akarsz, gazember?! A városôrség már a nyomodban van. Nem jutsz messzire, mocskos kalóz!", "Takarodj a házamból, gyilkos! Ôrség!", "Nem félek tôled, gazember! Hamarosan felakasztanak, nem menekülsz..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, nem aggódom túlságosan a riasztó miatt...", "Nincs esélyük elkapni engem."),
					RandPhraseSimple("Fogd be a pofád, " + GetWorkTypeOfMan(npchar, "") + ", vagy levágom a rohadt nyelved!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", te is kalózra akarsz vadászni! Figyelj, haver, maradj nyugodt, és életben maradsz..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! Még sosem láttam önt, senor. Merem feltételezni, hogy ön egy kapitány... Jól tippeltem? A nevem "+GetFullName(npchar)+", és a boltom az ön szolgálatára áll. Arany, ezüst, és még sok más, ami felkelti egy kíváncsi ember érdeklôdését.";
				Link.l1 = "Értem. Én vagyok " + GetFullName(pchar) + ". Örülök, hogy megismerhetem, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting() + ", ...senor! Örülök, hogy újra látom a boltomban. Szeretne néhány aranyrögöt vásárolni? Vagy esetleg ásványok érdekelnék ma?";
				link.l1 = "Mutasd meg az árudat, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Nem, nincs szükségem semmire, "+npchar.name+". Csak azért ugrottam be, hogy üdvözöljelek.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ahogy én is, senor. Megnézné az árumat? Biztos vagyok benne, hogy van valami, ami érdekelni fogja.";
			link.l1 = "Most vagyok itt elôször, és szeretnék egy kicsit többet megtudni errôl a településrôl.";
			link.l1.go = "info";
			link.l2 = "Akkor mutassa meg, mit kínál eladásra.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Kisvárosunk az aranybányának köszönhetôen épült fel. Aranyércet, ezüstöt és aranyrögöket bányásznak. Néha még drágaköveket is. Régen csak helyôrség volt itt, amíg barátságos indiánok és néhány fehér telepes nem csatlakozott hozzánk\nIgnacio Ortega kocsmát épített, és egy kicsit felvidította az életünket. Mindenféle kalandorok látogatják ezt a helyet azzal az ostoba szándékkal, hogy kiraboljanak minket. Nincs itt bíróságunk, így a számuk alacsonyra csökkent, miután több idiótát is felakasztottunk a város közepén\nAz aranyércet katonák és barátságos indiánok védelme alatt szállítják a hajókra, rögöket viszont itt, ebben a boltban lehet vásárolni\nMellesleg néha nagyon érdekes ásványokat kínálok, látogassatok el hozzám, ha van idôtök, mindig feltöltöm a készleteimet.";
			link.l1 = "Köszönöm az érdekes történetet! Majd észben tartom.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás fényes nappal!!! Mi folyik itt?! Várj, várj, haver...", "Hé, mit csinálsz ott?! Ki akarsz rabolni? Most megszívtad...", "Várj, mi a fenét csinálsz? Kiderült, hogy te egy tolvaj vagy! Vedd úgy, hogy itt a vége, te szemétláda...");
			link.l1 = LinkRandPhrase("Ördög!!!", "Caramba!!", "Ah, a francba!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
