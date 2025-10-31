#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Látod a bogarat. jelentsd az AT-nek, a haditengerészetnek.";
//	link.l1 = "Certainly!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hé, tûnjetek el, jó?! Ha elrontod az üzletemet, kitépem a szíved!";
			link.l1 = RandPhraseSimple("Hogy merészelsz fenyegetni engem, kurva?!", "Megfojtalak a szavaidtól, gazember!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Ó, értem már. Az üzlet az üzlet. Sok szerencsét.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Jó napot, a nevem " + GetFullName(NPChar) + ", és az öné?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns], PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "My name is " + GetFullName(pchar) + ".";
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Piát mindenkinek! Én vagyok a kapitány " + GetFullName(pchar) + ".", 
					"vagyok kapitány '" + PChar.Ship.Name + " és pár száz igazi ördög! He-he! A nevem " + GetFullName(pchar) + "."), 
				RandPhraseSimple("Engedjék meg, hogy bemutatkozzam, uraim. Én vagyok a kapitány " + GetFullName(pchar) + ".", 
					"Még nem mutatkoztunk be egymásnak. Én vagyok a '" + PChar.Ship.Name + " kapitánya  zászló alatt " + NationNameGenitive(sti(PChar.nation)) + ". A nevem " + GetFullName(pchar) + "."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Nos, itt mindenki ismer engem! A nevem " + GetFullName(NPChar) + ". Örülök a találkozásnak! Mit tehetek érted?";
		link.l1 = RandPhraseSimple("Üzletet akarok kötni veled!", "Szeretnék beszélni veled...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Nos, itt mindenki ismer engem! Én vagyok " + GetFullName(NPChar) + ", kapitány " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + ".";
			link.l2 = "Mi lenne, ha csatlakoznál hozzám? Két hajó jobb, mint egy. Együtt tisztességes üzletet köthetünk.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Szeretne tisztként szolgálni a hajómon?", "Szerintem jól megállná a helyét tisztként a hajómon. Mit szólsz hozzá?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Béta-teszt) Kiküldetések.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Béta-teszt) Párbajok.";
			link.l8.go = "outraged";
		}
		link.l9 = "Semmi.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hé, tûnjetek el, jó?! Ha elrontod az üzletemet, kitépem a szíved!";
			link.l1 = RandPhraseSimple("Hogy merészelsz fenyegetni engem, kurva?!", "Megfojtalak a szavaidtól, gazember!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Ó, értem már. Az üzlet az üzlet. Sok szerencsét.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Mára már mindent elmondtam neked!";
			link.l1 = "Ó, igen...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("Mire van szüksége" + GetFullName(pchar) + "?", "Ki az? Ó, te... Tûnj el, nem vagyok olyan hangulatban...");
		link.l1 = RandPhraseSimple("Mi a helyzet egy vállalkozással?", "akartam beszélni veled...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Nézd csak, ki van itt! Ez a " + GetFullName(pchar) + ". Van valami hír?", "Hogy vagy? Mit tehetek érted?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase(" Mi újság?", " Mik a hírek a szigetországban?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns] + " Mi újság?", PGG_Meet_BadRep[iAns] + " Mik a hírek a szigetországban?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Mi lenne, ha csatlakoznál hozzám? Két hajó jobb, mint egy. Együtt tisztességes üzletet köthetünk.", "Tapasztalt kapitánynak látszik. Akarsz a zászlóm alatt hajózni?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Ó, jaj nekem... Elsüllyedt a hajóm!", "Nézd, ki van itt?! Mi hozott ide? Egyébként elvesztettem a hajómat...");
				link.l3 = RandPhraseSimple("Kár. Talán legközelebb több szerencséd lesz.", "Ne mondd... Nos, itt az ideje, hogy elmenjek. Viszlát.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Szeretne tisztként szolgálni a hajómon?", "Szerintem jól megállná a helyét tisztként a hajómon. Mit szólsz hozzá?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "What's the news?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Micsoda ronda pofa. Egyszerûen verésért könyörög.", "Ó, a mi 'barátunk'. Szeretnél egy pár új lyukat a mellkasodba?");
			link.l8.go = "outraged";
		}
		link.l9 = "Semmi.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Már mondtam, hogy nem érdekel.", "Azt hittem, már mindent megbeszéltünk.");
			link.l1 = RandPhraseSimple("Hogy is felejthetném el?", "Rendben. Viszlát.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... talán nem. Másodszorra nem.", "És még azt hitted, hogy kétszer bekapom a csalit?!");
			link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Rendben. Akkor viszlát.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nem, azt hiszem, nem.", "Nem, én kapitány vagyok, és nem akarok tisztként szolgálni.");
			link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Rendben. Akkor viszlát.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Már van egy teljes készleted.", "Nem hiszem, hogy készen állsz arra, hogy parancsokat adj nekem.");
			link.l1 = RandPhraseSimple("Kár...", "Nos, a sors másképp rendelkezett.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("Pont erre volt szükségem! Pengéink megízlelik ellenségeink vérét! De van egy probléma - még mindig szükségem van " + NPChar.Quest.Officer.Price + " pezóra, hogy kifizessem az adósságaimat.", 
								"Úgy nézel ki, mint egy igazi öreg só. És ha hajlandó vagy fizetni " + NPChar.Quest.Officer.Price + " pezót, akkor jól tudnánk együtt dolgozni."), 
				LinkRandPhrase("Az ajánlata nagyon hízelgô számomra. Beleegyezem, hogy egy meglehetôsen szerény " + NPChar.Quest.Officer.Price + " pesóért dolgozom önnek.", 
							"Hmm... Úgy néz ki, mint egy tapasztalt tengerész. Talán el kellene fogadnom az ajánlatát, ha hajlandó fizetni nekem " + NPChar.Quest.Officer.Price + " pezó.", 
							"Azt hiszem, jól fogunk együtt dolgozni, kapitány. Csak " + NPChar.Quest.Officer.Price + " pezó, és megegyeztünk."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("Ez nekem megfelel. Csak remélem, hogy nem fogsz napi szinten felszámolni.", "Ez nagyon drága, de remélem, megéri."), 
				LinkRandPhrase("Egyetértek. Tekintsd magad a csapat részének.", "Hm... Azt hiszem, megengedhetem magamnak.", "Úgy tûnik, megéri. Vedd el az érméket!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("Nem érsz annyit. Viszlát...", "Túl drága nekem."), 
				LinkRandPhrase("Igen... A kapzsiság nem bûn...", "Te most rajtam nevetsz? Ennyi pénzért egy tucatot tudnék venni, mint te.", "Ez egy átverés. Honnan szerezzek ennyi pénzt?")), "kilépés");
		link.l3 = "Hmm... és mennyire vagy képzett?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Azt hiszem, gondjai vannak a pénzzel, kapitány.";
			link.l1 = "Ó... valóban.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Kiváló!", "Soha nem kételkedtem magában, kapitány.");
		link.l1 = "Ne késsen az indulásról.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Egy hiba, értesítsd a fejlesztôket.";
		link.l1 = "Úgy lesz!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Már mondtam, hogy nem érdekel.", "Azt hittem, már mindent megbeszéltünk.");
			link.l1 = RandPhraseSimple("Hogy is felejthetném el?", "Rendben. Viszlát.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Vitorlázni veled?! Elôbb nôj fel egy kicsit!", "Nem hiszem, hogy érdekelne!");
			link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Rendben. Akkor viszlát.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nem, azt hiszem, nem.", "Nem, köszönöm. Nem szeretek senki alatt szolgálni.");
			link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Rendben. Akkor viszlát.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
					RandPhraseSimple("Tetszel nekem! Megegyeztünk! Már hallom a zsebünkben a pezók csilingelését!", "Okos "+ GetSexPhrase("fickó vagy","lány") +"... Jól kellene együtt dolgoznunk!"), 
					LinkRandPhrase("Tetszik az ajánlatod. Egyetértek.", 
					"Ez érdekes. Tudod, szerintem együtt többet is elérhetünk!", "Az jó móka lesz. Megegyeztünk!"));
			link.l1 = RandPhraseSimple("Nagyszerû! Várlak a tengeren!", "Áll az alku! Remek csapat leszünk.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Szerintem már így is van elég társad.", "Már így is van elég hajód - miért lenne szükséged többre?");
			link.l1 = "Hát... Talán igazad van.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("Unatkozom veled!!! Elhagyom az osztagotokat!", "türelmemnek vége! Elmegyek."), 
					RandPhraseSimple("belefáradtam az eszkalációidba, 'admirális'... Engedjétek meg, hogy távozzak.", "Elegem van a parancsnokságából, és elhagyom az osztagát."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Rendben, akkor tûnj el.", "Rendben, menj, ahová csak akarsz."),
					RandPhraseSimple("Rendben. Nem foglak tartani.", "Ez a te döntésed. Kívánok neked jó szelet."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... mit szólnál egy kis prémiumhoz?", "Caramba! Ó, a fenébe is, talán maradnál? Még a legénységednek is tudok fizetni egy kis pluszt!"),
					RandPhraseSimple("Nem szívesen válnék meg tôled... Talán egy kis kárpótlással elintézhetnénk a vitáinkat?", "Mi lenne, ha megemelnénk a bérét?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Nekem elég volt egy alkalom. Többé nem bízom az ígéreteidben!", "Nem fogsz pénz nélkül elcsábítani! A döntésem végleges!");
			link.l1 = RandPhraseSimple("Rendben, akkor sok szerencsét neked.", "Aztán tûnj el, és gondoskodj róla, hogy soha többé ne lássalak!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("Prémium? Rendben! Egy " + NPChar.Quest.Companion.Price + " pezó összeg nekem megfelel.", 
						"Nos, talán, ha hajlandó fizetni a legénységemnek " + NPChar.Quest.Companion.Price + " pesót, talán rávehetném ôket, hogy maradjanak."), 
					RandPhraseSimple("Rendben! Egy kis " + NPChar.Quest.Companion.Price + " pezó felárért maradhatok!",
						NPChar.Quest.Companion.Price + " egy idôre kielégít engem és a legénységemet."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Most nevetsz rajtam, vagy mi?! Tûnj el, most!", "Ha! Sokkal szívesebben költeném ezt a pénzt valami hasznosabbra!"),
					RandPhraseSimple("Ó, ne! Nem vagyok olyan gazdag!", "Viszlát. Ennyit fogok fizetni."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Kiváló! Itt a prémiuma!", "Soha nem kételkedtem abban, hogy minden a pénzrôl szól!"),
					RandPhraseSimple("Excellent! Örülök, hogy maradsz.", "Itt van, amit ígértem."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Válaszd kia sablont!";
		link.l1 = "1. küldetés sablon - tenger.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "VÁLASZTOTT! 1. küldetés sablon - szárazföld.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "1. küldetés sablon - tenger.";
		link.l1 = "Ó, igen...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "VÁLASZTOTT! 1. küldetés sablon - szárazföld.";
		link.l1 = "Ó, igen...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Már mindent elmondtam neked!";
			link.l1 = "Ó, igen...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Milyen üzlet?... Hic! Nem látod - én és a haverok jól érezzük magunkat!... Hic...",
									"Ehh... Ma nincs üzlet!");
		link.l1 = "Értem...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "Milyen beszélgetés? Bár még idôben érkeztél. Ha üzletrôl van szó, mindig készen állok!";
					link.l1 = "Hmm. Mirôl beszélsz?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...csak én és az ördög ismerjük azt a helyet, és aki utoljára marad életben, az mindent megkap!...", 
							 "...mire Meinard azt válaszolta: 'Nem várok tôled kegyelmet, és nem is adok'", 
							 "...és egyszer a nyílt tengeren, amikor már kissé be volt állva, azt javasolta: 'csináljuk ott a poklot magunknak, és meglátjuk, ki marad ki utoljára'.") + 
							 PCharRepPhrase(LinkRandPhrase("Na, itt egy másik kalóz!",
									"Uraim, gondolom, egy szerencselovag ül az asztalunknál?",
									"Puskapor és vér szagát érzem! Egy filibuster a fedélzeten!"), 
								LinkRandPhrase("A tisztességes kapitányok ritkaságszámba mennek ezeken a vizeken.",
									"A nemesség manapság már nem divat.",
									"Ó, hát ez egy tisztességes kapitány, egyáltalán nem olyan, mint ti, gyilkosok! He-he!"));
						link.l1 = "Nem kiabálok, csak mondom, hogy van egy jövedelmezô üzlet!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Óvatosan, óvatosan! Ó! Ismerlek. Te vagy " + GetFullName(PChar) + ". Sokat hallottam rólad.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Kapitány vagyok " + GetFullName(pchar) + ".", 
						"vagyok kapitány '" + PChar.Ship.Name + " és pár száz igazi ördög! He-he! A nevem " + GetFullName(pchar) + ".") + " De nem emlékszem rád.", 
					RandPhraseSimple("Engedjék meg, hogy bemutatkozzam, uraim. Én vagyok a kapitány " + GetFullName(pchar) + ".", 
						"Még nem mutatkoztunk be egymásnak. Én vagyok a '" + PChar.Ship.Name + " kapitánya a " + NationNameGenitive(sti(PChar.nation)) + "zászló alatt. A nevem " + GetFullName(pchar) + ".") + " De nem emlékszem rád.");
//			link.l1 = "Hmm... and just who are you? I don't remember you.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Szia, " + GetFullName(NPChar) + ". Hogy megy az élet?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Én vagyok " + GetFullName(NPChar) + ", kapitány " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + NPCharRepPhrase(NPChar, ". A leghírhedtebb korzózó az egész spanyol mainban.", ". Csak egy tengerész.");
		link.l1 = "Igen, most már emlékezni fogok rád.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + rand(2);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Üzleti ügyem van veled, "+ GetSexPhrase("haver","lass") +". Tudom, hogy bízhatok benned, de a kocsmában nem tudom megbeszélni - túl sok a rossz fül. Várni foglak a hajóm fedélzetén. Az öreg teknôm neve '" + NPChar.Ship.Name + "'.";
//			link.l1 = "Spit it out now, I have no time for visits.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Van egy érdekes ügyem számodra és a gyilkosaid számára.", 
								"Ha egyesítjük erôinket, akkor valóban egy igazán nagy nyereményt nyerhetünk! Persze közben meg kell ölnünk valakit. He-he."), 
							RandPhraseSimple("Van egy üzleti ajánlatom az ön számára, kapitány.", 
							"Kapitány, az ön hírneve páratlan, ezért felajánlom, hogy részt vesz egy csábító ügyletben.")) + 
						RandPhraseSimple("Csak kettônk között. Beszéljük meg a '" + NPChar.Ship.Name + " kórteremben a legfinomabb sör hordója mellett. Még ma.", "Ne ott beszéljük meg, tárgyaljuk meg a részleteket '" + NPChar.Ship.Name + " nyugodtan és csendben. És kérem, ne tartson túl sokáig.");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("A pokolba ezekkel a késésekkel! Ha jó, azonnal tudni akarom, és még inkább, ha rossz!", 
								"Nincs értelme az ilyen rövid drótoknak! A kocsmában van egy alkalmas helyiség - menjünk oda!"), 
							RandPhraseSimple("És miért nem beszélhetjük meg az ajánlatodat rögtön tudd meg, a kocsma szobájában?", 
								"Attól tartok, nem sok kedvem van meglátogatni a hajóját. Ha valamire szüksége van, köpje ki itt és most!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Nem kellene a kocsmában üzletrôl beszélnünk - túl sok a rossz fül. Várlak a hajómon '" + NPChar.Ship.Name + ". Ott fogunk beszélgetni.";
			link.l1 = "Nincs idôm, és nem szeretek látogatóba menni.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Majd én megyek. De ha csak az idômet vesztegeted, kitépem a nyelved!", 
					RandSwear() + "Rendben, várj meg. Remélem, az ajánlatod megéri. És eszedbe ne jusson trükközni velem!"), 
				RandPhraseSimple("Örömmel elfogadom a meghívását, kapitány.", 
					"Kíváncsivá tettél. Természetesen el fogok jönni."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Ó, tengeribeteg vagy, ugye? Fuss és bújj anyukád szoknyája alá!", 
					"Túlságosan félsz?! Tûnj el!"), 
				RandPhraseSimple("Nem lehet. Ha nem érdekel az arany, az a te döntésed.", 
					"Erre van, és nem másra. Ha nem akarod - rendben, van sok más is."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! Bátor vagy, ugye? Rendben, megyek!", 
					"Látom, hogy tudod tartani magad a szavad, kapitány. Rendben, várjatok meg."), 
				RandPhraseSimple("Rendben, egyetértek.", 
					"Maga aztán tud beszélni. Készen állok, hogy megbeszéljük az üzletet a hajóján."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! Arra gondoltál, hogy a hajódra csalogatsz és ott megölsz? Az nem fog menni!", 
					"A szavaid egy fillért sem érnek! Nem üzletelek veled!"), "Kétes ajánlat. Vissza kell utasítanom.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rumot kérek! Te pedig tûnj el a szemem elôl!", 
					"Nem beszéltünk már meg mindent?"), 
				RandPhraseSimple("Menj a saját dolgodra. Nekem dolgom van.", 
					"Nem hiszem, hogy van mit megbeszélnünk."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Mondtam neked, hogy a hajómon foglak várni!";
		link.l1 = "Oh... persze...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Ó, nem, ez nem fog menni... Nem túl sok neked ez a hajó, "+ GetSexPhrase("pajtás","lass") +"?", 
					"Ha! Egy ekkora cégnél nem lehet titokban tartani a dolgokat. Tûnjetek el!");
			link.l1 = RandPhraseSimple("Ahogy kívánod!", 
					"Rendben. Nem mintha érdekelne.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Nagyszerû. Most már biztos vagyok benne, hogy nincsenek rossz fülek a környéken, és a matrózaimat már értesítették. Szóval az ajánlatom az, hogy szerezzünk néhány gazdátlan cuccot.";
//			link.l1 = "And what's so hard about it? Why would you need me for that, in the first place?";
			Dialog.Text = RandPhraseSimple("Üdvözöljük a fedélzeten, kapitány!", 
					"Nagyszerû. Most már biztos vagyok benne, hogy nincsenek rossz fülek a környéken, és a matrózaimat már értesítették. Szóval az ajánlatom az, hogy szerezzünk néhány gazdátlan cuccot.") + 
					" Szóval az ajánlatom az, hogy szerezzek néhány gazdátlan cuccot.";
			link.l1 = RandPhraseSimple("És mi olyan nehéz ebben? Miért lenne szükséged rám egyáltalán?", 
					"Ownerless?! Biztos csak viccelsz!");
		}
		else
		{
			Dialog.Text = "Most már biztos vagyok benne, hogy nincsenek rossz fülek a környéken - csak rajta, köpd ki!";
			link.l1 = "Szóval az ajánlatom az, hogy szerezzünk néhány gazdátlan cuccot.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Nos, vannak emberek, akik sajátjuknak tekintik, és ôket meg kell gyôzni az ellenkezôjérôl.", 
					"Persze, valakit meg kell ölni - de biztos, hogy ez nem lesz probléma?");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Térjünk a tárgyra!", 
					"Ennek mészárlás szaga van! És hol vannak?"), 
				RandPhraseSimple("Szeretnék több részletet megtudni az ajánlatáról.", 
					"Pontosan mit ajánl nekem?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Maga átver engem. Ebben nem veszek részt!", 
					"Ez könnyûnek tûnik, de nem bízom benned! Azt akarod, hogy kihúzzam neked a gesztenyét a tûzbôl? Nos, nem értek egyet!"), 
				RandPhraseSimple("Ígéretesen hangzik, de inkább passzolok.", 
					"Nem, én nem lopok, szeretem, ha helyette ajándékot adnak."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "És mi olyan nehéz ebben? Miért lenne szükséged rám egyáltalán?";
			link.l1 = "Nos, vannak emberek, akik a sajátjuknak tekintik, és ôket meg kell gyôzni az ellenkezôjérôl.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "Egy lakókocsi, amely a " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + "tulajdonát képezi, és amely a következôket szállítja ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Rabszolgák";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + 
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Ne húzd, köpd ki!", 
					"Igazam volt veled kapcsolatban, mit tudsz te még?"), 
				RandPhraseSimple("Ez nagyon érdekes, kérlek folytasd!", 
					"A am "+ GetSexPhrase("minden","minden") +" fül!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Ez csábítóan hangzik, de én mégis visszautasítom. Nem kell veszekednem a " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ".", 
					"Lakókocsi? Tulajdonos nélkül?! Ezer katonának kellene ôriznie! Nem, az nem fog menni. Elmegyek."), 
				RandPhraseSimple("Nem, nem állok háborúban a " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", tehát nem érdekel.", 
					"A válaszom nem! Nem fogom tönkretenni a kapcsolataimat a " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Ez a mészárlás szaga! Mi a helyzet a részletekkel?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Csak a " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " áll rendelkezésünkre, hogy elfogjuk ôket.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("A " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " a karaván túl messzire megy, és nem fogjuk tudni lefutni.", 
						"Pontosan " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " napunk van arra, hogy mindet megöljük és megszerezzük a zsákmányt!"), 
					RandPhraseSimple("Csak " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " nap áll rendelkezésünkre az egész akcióra.", 
						"Sietnünk kell, " + PChar.Name + ". Már csak " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "áll rendelkezésünkre."));
			link.l1 = RandPhraseSimple("Idôben megcsináljuk! Vitorlát bontunk még ma.", "Akkor ne vesztegessük az idôt. Rendeljük meg, hogy még ma vitorlát bontunk.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "Ez nagyon érdekes, kérem folytassa.";
			link.l1 = "Csak a " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " áll rendelkezésünkre, hogy elfogjuk ôket.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Ne vesztegessük az idôt! Induljunk!";
		link.l1 = "Indulás!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + "Csalódtam magában, kapitány. Azt hitte, hogy meghívom a "+ RandPhraseSimple("vasárnapi misére?!!!", "egy gyerekjátékra!???"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ez a te dolgod. És rajtam múlik, hogy eldöntsem.", 
					"Nem fogok kötélen lógni pár pezóért."), 
				RandPhraseSimple("A döntésem végleges, kapitány.", 
					"Nincs több megbeszélnivalónk."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Ó, ugyan már! Minden simán fog menni, és senki sem fog tudni semmit. Mindenkit meg fogunk ölni."), 
				RandPhraseSimple("Hová megy, kapitány? Talán a hatóságokhoz?", 
					"Elég bölcs dolog úgy besétálni egy tigris barlangjába, hogy azt hiszed, könnyen kijutsz onnan."));
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Menj, csókold meg a tengeri ördögöt! Én vagyok a kapitány " + GetFullName(PChar) + " és nem érdekelsz! Elmegyek!", 
					"Az ördögre esküszöm, tényleg megôrjítesz!"), 
				RandPhraseSimple("Az ajánlatod nem érdekel engem, és nincs mit megbeszélnünk. Viszontlátásra.", 
					"Azt hiszem, nincs több megbeszélnivalónk. Sajnálom, elfoglalt vagyok, és mennem kell."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(RandPhraseSimple("Fogd meg "+ GetSexPhrase("ôt","ôt") +"! Kössétek "+ GetSexPhrase("ôt","ôt") +" az ágyúhoz! Lássuk milyen színû "+ GetSexPhrase("az ô","az ô") +" belek!!!", 
					"Hé! Johnny! Henderson! Fogd meg azt a "+ GetSexPhrase("gazembert","lányt") +"! Ne hagyjátok "+ GetSexPhrase("ôt","ôt") +" a mentôcsónakhoz jutni!!!"), 
				RandPhraseSimple("Kár, kapitány úr! Azért remélem, hogy tetszene a rakodótér. Aztán majd eldöntjük, hogy mi legyen veled.", 
					"A fehér rabszolgák nem arról híresek, hogy sokáig élnek, kapitány, úgyhogy válasszon: vagy Hends fejbe lövi, vagy egy kôbányában tölti hátralévô életét."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Megeszem veled a mocskos beledet, " + GetFullName(NPChar) + "!!!", 
					"Adjatok utat! Gazemberek! Megöllek titeket ott, ahol álltok!"), 
				RandPhraseSimple("Az ajánlatod elfogadhatatlan... És nagyon bölcstelen!!!", 
					"Nem vagytok olyan vendégszeretôek, ahogy látom... Utat!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "Szóval, " + GetFullName(PChar) + ", látom, hogy hibát követtem el, amikor összekevertelek veled. Most már nincs zsákmány számunkra. Viszlát!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Az istenit! Elkéstünk - és mindez a lusta idióták miatt! Most már nincs zsákmány, amit megoszthatnánk veletek, " + GetFullName(PChar) + ". Húzzátok fel a vitorlát! Elmegyünk innen! ", 
					"Szóval, " + GetFullName(PChar) + ", látom, hogy hibát követtem el, amikor összekeveredtem veled. Most már nincs zsákmány számunkra. Viszlát!"), 
				RandPhraseSimple("Eltûntek - és mindez a te késésed miatt! Most különbözô utakon járunk, " + GetFullName(PChar) + ".", 
					"Kizárt, hogy most már le tudjuk futtatni a karavánt. Hibát követtem el, amikor összekeveredtem veled. Viszontlátásra!"))
		link.l1 = PCharRepPhrase(RandPhraseSimple("A pokolba azzal a karavánnal! A gyöngybúvárok még jobbak, és nincs kockázat!", 
					"A szerencse velünk van, és holnap egy újabb nap! Rengeteg szánalmas kereskedô van a tengereken, akik csak arra várnak, hogy elvegyük a pénzüket!"), 
				RandPhraseSimple("Valóban kár, hogy egy ilyen zseniális akció teljes kudarcba fulladt! Viszontlátásra!", 
					"Az ember javasol, Isten pedig rendel... Isten veled!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Ó, mi a fenéért keveredtem össze veled. Mindent tönkretettél. Szóval, most büntetést kell fizetned nekem " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + ".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Vérszomjas "+ GetSexPhrase("gazember","mocsok") +"! Minden lement egyenesen a tenger ördögébe!" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pezó a szögre, és tûnj a szemem elôl!", 
						"Nelson admirálisnak képzelte magát? Elsüllyesztetted az összes zsákmányt, "+ GetSexPhrase("idióta","ostoba nôszemély") +"! Add ide most " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pezót és tûnj el!"), 
					RandPhraseSimple("Elhatároztad, hogy itt háborút indítasz! Ez teljesen elfogadhatatlan! De azt hiszem, elfelejthetjük, ha fizetsz nekünk " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesót.", 
						"A módszereik teljesen elfogadhatatlanok! Tönkretetted az egész ügyet! Azonnal fizesse ki nekünk a részünket " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pezó összegben, és menjen, ahová akar!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Ha én nem lennék, mostanra már rákokat etetnél, te mohó szemétláda!", 
						"Ó, igen, hagynom kellett volna, hogy a zászlóshajójuk a fedélzetre vigyen - akkor most nem mérgeznéd a levegôt, az udvaron hintázva!"), 
					RandPhraseSimple("A követeléseid nem helyénvalóak, a célozgatásaid pedig sértôek!", 
						"Nem egyeztünk meg a büntetésben, ezért nem fizetek neked semmit!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Most nem tudok neked csatát adni, és ezt te is tudod! Fojtsd meg a pezódat!", 
								" pezó?!! Nos, a szerencse asszony ma biztosan nem mosolyog rám. Egyetértek."), 
							RandPhraseSimple("A követeléseid felháborítóak, de azt hiszem, nincs más választásom.", 
								"Az étvágyad túlzó, de egyet kell értenem!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Ó, mi a fenéért keveredtem össze veled? Mindent tönkretettél.";
			link.l1 = "Ó, ugyan már! Te magad is láttad, hogy nincs más lehetôség.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Tehát a zsákmányunk teszi ki " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ". Váljunk szét.";
			Dialog.Text = PCharRepPhrase("Ez egy forró üzlet volt! Szóval, a zsákmányunk teszi ki " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", 
					"Kiváló munka, kapitány! A zsákmányunk " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text + PCharRepPhrase(" Az én részem ", " Az én hajóm részesedése - ");
			}
			else
			{
				Dialog.Text = Dialog.Text + " A te részed ";
			}
			Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Minden rendben van! A hajókat már rakodják!", "Igen, minden rendben van. Az alku az alku."), 
					RandPhraseSimple("A számításai helyesek. Egyetértek.", "Ha osztozkodásról van szó, akkor te feddhetetlen vagy."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Követelni mered a részed? Azonnal fel kellene akasztani az udvaron!", 
						"A te részed? Itt mindenki magának való. Ha neked nem maradt semmi, az a te bajod!"), 
					RandPhraseSimple("Nem hiszem, hogy számíthatsz bármiféle részesedésre.", 
						"A válaszom: nem! Nem osztozom az olyan gazemberekkel, mint te!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Nos, akkor rendben, nem fogok vitatkozni! Viszontlátásra!", 
					"Ne ontjuk a vért és ne rontsuk tovább a helyzetet! Legközelebb több szerencsénk lesz!"), 
				RandPhraseSimple("Nos, viszlát, kapitány úr, nem vagyok abban a helyzetben, hogy követeléseket támasszak...", 
					"A hajóm veszteségei és sérülései nem teszik lehetôvé, hogy ragaszkodjak az igazságos döntéshez. Ezt a lelkiismeretére bízom, kapitány úr!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Kedvezô szelet nektek!", "Hét láb a hajógerinc alatt!"), 
				RandPhraseSimple("Isten veled! Remélem, a friss tengeri levegô jót tesz majd neked!", 
					"Remélem, hogy szerencsétlenségeink nem teszik még elviselhetetlenebbé, kapitány úr! Viszontlátásra!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Nem értetted meg! Megvehetnéd az életed helyette! Fogjátok el a rohadékot!", 
						"Vagy azt hiszed, hogy csak játszadozunk veled? Hát, ha egyszer kielhaulozunk, akkor engedelmesebb leszel!"), 
					RandPhraseSimple("Akkor meg kell rövidítenünk az életét, kapitány! Ha nem mész el barátságosan, hamarosan találkozol Szent Mártonnal!", 
						"Választás nélkül hagysz, " + GetFullName(PChar) + "! Elveszem, ami az enyém, akár tetszik, akár nem!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Az ördögre esküszöm, ezért megfizetsz!!!", 
						"Yo-ho! Akkor menj és kapj el, kapitány " + GetFullName(PChar) + "! "), 
					RandPhraseSimple("A vágás hosszú és mély lesz!", 
						"Szeretnél gyorsan meghalni, vagy egy kis szenvedéssel?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Nem akarok veled többet foglalkozni!";
		link.l1 = "Semmi gond.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Jó volt veled üzletelni. Sok szerencsét.";
		link.l1 = "Neked is.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("Ez egy igazi mészárlás volt! Kár, hogy nem volt velük egy leány sem! A zsákmány kárpótol  " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", "Nem rossz, kapitány! A zsákmány teszi ki " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text + " Az én részem ";
		}
		else
		{
			Dialog.Text = Dialog.Text + " A te részed ";
		}
		Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Teljesen csak, az istenit!", "Minden tökéletesen rendben van, az istenit!"), 
			RandPhraseSimple("A számításaid helyesek. Egyetértek.", "Ha osztásról van szó, akkor te feddhetetlen vagy."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
