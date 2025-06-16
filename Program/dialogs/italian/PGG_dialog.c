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
//	Dialog.Text = "Se notate un bug... segnalatelo all'AT, per la Marina.";
//	link.l1 = "Certo!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Ehi, sparisci, non ti pare! Se rovini il mio affare, ti strappo il cuore!";
			link.l1 = RandPhraseSimple("Osi minacciarmi, cane?!","Ti farò soffocare con le tue parole, mascalzone!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, capisco. Gli affari sono affari. Buona fortuna.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Buon pomeriggio, mi chiamo "+GetFullName(NPChar)+", e il tuo?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "Il mio nome è "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Birra per tutti! Io sono il capitano "+GetFullName(pchar)+".","Sono il capitano di '"+PChar.Ship.Name+" e un paio di centinaia di veri diavoli! He-he! Il mio nome è "+GetFullName(pchar)+"."),RandPhraseSimple("Permettetemi di presentarmi, signori. Sono il capitano "+GetFullName(pchar)+".","Non siamo ancora stati presentati. Sono il capitano della nave '"+PChar.Ship.Name+" sotto la bandiera di "+NationNameGenitive(sti(PChar.nation))+". Il mio nome è "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Beh, tutti qui mi conoscono! Io sono "+GetFullName(NPChar)+". Piacere di conoscerti! Cosa posso fare per te?";
		link.l1 = RandPhraseSimple("Ho affari con te!","Voglio parlare con te...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Beh, qui tutti mi conoscono! Io sono "+GetFullName(NPChar)+", capitano "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "Che ne dici di unirti a me? Due navi sono meglio di una. Possiamo fare un buon affare insieme.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Vorresti servire come ufficiale sulla mia nave?","Credo che tu possa fare un buon ufficiale sulla mia nave. Che ne dici?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Missioni.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Duelli.";
			link.l8.go = "outraged";
		}
		link.l9 = "Niente.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Ehi, sparisci, non vuoi! Se rovini il mio affare, ti strapperò il cuore!";
			link.l1 = RandPhraseSimple("Osi minacciarmi, canaglia?!","Ti farò soffocare con le tue parole, mascalzone!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, capisco. Gli affari sono affari. Buona fortuna.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Ti ho già detto tutto per oggi!";
			link.l1 = "Oh, sì...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("Di cosa hai bisogno"+GetFullName(pchar)+"?","Chi è quello? Ah, sei tu... Vattene, non sono dell'umore...");
		link.l1 = RandPhraseSimple("E che ne dici di un affare?","Volevo parlarti...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Oh, guarda chi è qui! È "+GetFullName(pchar)+". Qualche notizia?","Come stai? Cosa posso fare per te?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase("Quali sono le novità?","Quali sono le novità sull'arcipelago?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+"Quali sono le novità?",PGG_Meet_BadRep[iAns]+"Quali sono le novità sull'arcipelago?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Che ne dici di unirti a me? Due navi sono meglio di una. Possiamo fare un buon affare insieme.","Sembri un capitano esperto. Vuoi navigare sotto la mia bandiera?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Oh, disgrazia a me... La mia nave è affondata!","Guarda chi è qui?! Cosa ti ha portato qui? Tra l'altro ho perso la mia nave...");
				link.l3 = RandPhraseSimple("Un peccato. Forse avrai più fortuna la prossima volta.","Non dire... Beh, è ora per me di andare. Ci vediamo.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Vorresti servire come ufficiale sulla mia nave?","Credo che tu potresti fare un ottimo ufficiale sulla mia nave. Cosa ne dici?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Quali sono le novità?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Che brutto muso. Chiede proprio di essere picchiato.","Oh, il nostro 'amico'. Vorresti un paio di nuovi fori nel petto?");
			link.l8.go = "outraged";
		}
		link.l9 = "Niente.";
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
			Dialog.Text = RandPhraseSimple("Ti ho già detto che non sono interessato.","Pensavo che avessimo già discusso di tutto.");
			link.l1 = RandPhraseSimple("Come potrei dimenticare?","Va bene così. Addio.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Mmm... forse no. Non una seconda volta.","E pensavi che avrei abboccato due volte?!");
			link.l1 = RandPhraseSimple("Bene, come vuoi tu...","Bene. Ci vediamo, allora.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Mmm... No, immagino di no.","No, sono un capitano, e non voglio servire come ufficiale.");
			link.l1 = RandPhraseSimple("Ebbene, come desideri...","Bene. Ci vediamo, allora.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Hai già un set completo.","Non credo che tu sia pronto a darmi ordini.");
			link.l1 = RandPhraseSimple("Peccato...","Ebbene, il destino ha decretato diversamente.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("È proprio quello di cui avevo bisogno! Le nostre lame assaggeranno il sangue dei nostri nemici! Ma c'è un problema - mi serve ancora "+NPChar.Quest.Officer.Price+" pesos per saldare i miei debiti.","Sembri un vero vecchio lupo di mare. E se sei disposto a pagare "+NPChar.Quest.Officer.Price+" pesos, potremmo lavorare bene insieme."),LinkRandPhrase("La tua offerta mi lusinga molto. Accetto di lavorare per te per una tariffa piuttosto modesta di "+NPChar.Quest.Officer.Price+" pesos.","Hmm... Sembri un marinaio esperto. Forse, dovrei accettare la tua offerta se sei disposto a pagarmi "+NPChar.Quest.Officer.Price+" pesos.","Credo che lavoreremo bene insieme, capitano. Solo "+NPChar.Quest.Officer.Price+" pesos, e abbiamo un accordo."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Mmm... e quanto sei qualificato?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Credo che tu abbia problemi con i soldi, capitano.";
			link.l1 = "Oh... davvero.";
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

		Dialog.Text = RandPhraseSimple("Eccellente!","Non ho mai dubitato di te, capitano.");
		link.l1 = "Non fare tardi per la partenza.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Un bug, informa gli sviluppatori";
		link.l1 = "Lo farò!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Ti ho già detto che non sono interessato.","Pensavo che avessimo già discusso di tutto.");
			link.l1 = RandPhraseSimple("Come potrei dimenticare?","Va bene. Addio.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Veleggiare con te?! Cresci un po' prima!","Non credo di essere interessato!");
			link.l1 = RandPhraseSimple("Beh, come desideri...","Bene. Ci vediamo, allora.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Mmm... No, immagino di no.","No, grazie. Non mi piace servire sotto qualcuno.");
			link.l1 = RandPhraseSimple("Bene, come desideri...","Bene. Allora ci vediamo.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Mi piaci! Hai fatto un affare! Già sento il tintinnio dei pesos nelle nostre tasche!","Sei astuto "+GetSexPhrase("ragazzo","ragazza")+"... Dovremmo lavorare bene insieme!"),LinkRandPhrase("Mi piace la tua offerta. Accetto.","È interessante. Sai, penso che insieme possiamo fare di più!","Dovrebbe essere divertente. Abbiamo un accordo!"));
			link.l1 = RandPhraseSimple("Ottimo! Ti aspetterò in mare!","Affare fatto! Faremo un grande equipaggio.");
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
			Dialog.Text = RandPhraseSimple("Credo che tu abbia già abbastanza compagni.","Hai già abbastanza navi - perché ne avresti bisogno di altre?");
			link.l1 = "Sì... Forse, hai ragione.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Sono stufo di te!!! Sto lasciando il tuo squadrone!","La mia pazienza è finita! Me ne vado."),RandPhraseSimple("Sono stanco delle tue scorribande, 'ammiraglio'... Permettimi di prendere il mio congedo.","Sono stanco del tuo comando e sto lasciando il tuo squadrone."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Bene, sparisci, allora.","Bene, vai dove preferisci."),RandPhraseSimple("Bene. Non ti tratterrò.","Questa è la tua scelta. Ti auguro un vento favorevole."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... che ne dici di una piccola aggiunta?","Caspita! Oh, diavolo, forse, resteresti? Posso anche pagare un po' di più i tuoi marinai!"),RandPhraseSimple("Mi dispiacerebbe molto separarmi da te... Forse, un piccolo compenso può risolvere le nostre dispute?","Che ne dici di aumentare il tuo stipendio?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Una volta è stata sufficiente per me. Non mi fiderò più delle tue promesse!","Non mi attirerai con nessun denaro! La mia decisione è definitiva!");
			link.l1 = RandPhraseSimple("Bene, quindi buona fortuna a te.","Allora sparisci e assicurati che non ti vedrò mai più!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Un premio? Bene! Una somma di "+NPChar.Quest.Companion.Price+" pesos mi andranno benissimo.","Ebbene, forse, se sei pronto a pagare al mio equipaggio "+NPChar.Quest.Companion.Price+" pesos, potrei persuaderli a restare."),RandPhraseSimple("Bene! Posso restare per una piccola somma di "+NPChar.Quest.Companion.Price+" pesos!",NPChar.Quest.Companion.Price+" soddisferà me e il mio equipaggio per un po'."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Stai ridendo di me o cosa?! Vattene, adesso!","Ha! Preferirei di gran lunga spendere questi soldi per qualcosa di più utile!"),RandPhraseSimple("Oh no. Non sono così ricco!","Addio. Sto per pagare questo tanto."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Eccellente! Ecco la tua ricompensa!","Non ho mai dubitato, si trattava sempre di soldi!"),RandPhraseSimple("Eccellente! Sono contento che tu stia rimanendo.","Ecco quello che ho promesso."));
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
		Dialog.Text = "Scegli il modello!";
		link.l1 = "Modello di missione 1 - mare.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "SELEZIONATO! Modello di missione 1 - terra.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Modello Missione 1 - mare.";
		link.l1 = "Oh, sì...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SELEZIONATO! Modello di missione 1 - terra.";
		link.l1 = "Oh, sì...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Ti ho già detto tutto!";
			link.l1 = "Oh, sì...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Che affari?.. Hic! Non vedi - io e gli amici ci stiamo divertendo un sacco!.. Hic...","Ehh... Nessun affare oggi!");
		link.l1 = "Capisco...";
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
					Dialog.Text = "Di che parli? Anche se, sei in tempo. Quando si tratta di affari, sono sempre pronto!";
					link.l1 = "Mmm. Di cosa stai parlando?";
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

						Dialog.Text = LinkRandPhrase("...solo io e il diavolo conosciamo quel posto, e l'ultimo a restare in vita avrà tutto!..","...e Meinard rispose: 'Non mi aspetto alcuna pietà da te e non te ne darò, nemmeno'","...e una volta in mare aperto, quando era già un po' brillo, suggerì: 'Facciamo un inferno per noi stessi lì e vediamo chi resiste fino alla fine'.")+PCharRepPhrase(LinkRandPhrase("Ecco un altro pirata!","Signori, credo che abbiamo un gentiluomo di fortuna al nostro tavolo, vero?","Sento l'odore della polvere da sparo e del sangue! Un filibustiere a dritta!"),LinkRandPhrase("Capitani decenti sono una razza rara in queste acque.","La nobiltà è fuori moda in questi giorni.","Oh, ecco un capitano decente, per niente come voi, tagliagole! He-he!"));
						link.l1 = "Non sto urlando, ti sto dicendo - c'è un affare vantaggioso!";
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
		Dialog.Text = "Attento, attento! Oh! Ti conosco. Tu sei "+GetFullName(PChar)+". Ho sentito molto di te.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Sono il capitano "+GetFullName(pchar)+".","Sono il capitano di '"+PChar.Ship.Name+" e un paio di centinaia di veri diavoli! He-he! Il mio nome è "+GetFullName(pchar)+".")+" Ma non mi ricordo di te.",RandPhraseSimple("Permettetemi di presentarmi, signori. Sono il capitano "+GetFullName(pchar)+".","Non ci siamo ancora presentati. Sono il capitano della nave '"+PChar.Ship.Name+" sotto la bandiera di "+NationNameGenitive(sti(PChar.nation))+". Il mio nome è "+GetFullName(pchar)+".")+" Ma non mi ricordo di te.");
//			link.l1 = "Mmm... e tu chi sei? Non ti ricordo.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Ciao, "+GetFullName(NPChar)+". Come va la vita?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Sono "+GetFullName(NPChar)+", capitano "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". Il corsaro più famigerato dell'intero Mare Spagnolo.",". Solo un marinaio.");
		link.l1 = "Sì, ora mi ricorderò di te.";
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
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Ho affari con te, "+GetSexPhrase("compagno","ragazza")+". So che posso fidarmi di te, ma non posso discuterne nella taverna - troppe orecchie indiscrete. Ti aspetterò a bordo della mia nave. Il nome della mia vecchia tinozza è '"+NPChar.Ship.Name+"'. ";
//			link.l1 = "Sputalo fuori ora, non ho tempo per le visite.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Ho un'affare interessante per te e i tuoi tagliagole.","Se uniamo le forze, potremmo davvero vincere un grande premio! Naturalmente, dovremo uccidere qualcuno nel processo. He-he."),RandPhraseSimple("Ho un'offerta di affari per te, capitano.","Capitano, la tua reputazione è senza eguali, e quindi ti offro di partecipare a un'affare allettante."))+RandPhraseSimple("Solo tra noi due. Discutiamone nella sala degli ufficiali di '"+NPChar.Ship.Name+" sopra la botte della birra più scelta. Oggi.","Non dovremmo discuterne lì, negoziamo i dettagli su '"+NPChar.Ship.Name+" in pace e tranquillità. E per favore non impiegate troppo tempo.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("All'inferno con questi ritardi! Se è buono, voglio saperlo subito, e ancora di più se è cattivo!","Non c'è senso in questi fili così corti! C'è una stanza adatta nella taverna - andiamo là!"),RandPhraseSimple("E perché non possiamo discutere la tua offerta proprio ora, nella stanza della taverna?","Temerei che ho pochissima voglia di visitare la tua nave. Se hai bisogno di qualcosa, sputalo fuori qui e ora!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Non dovremmo discutere di affari nella taverna - troppi orecchie sbagliate. Ti aspetto sulla mia nave '"+NPChar.Ship.Name+". Parleremo lì.";
			link.l1 = "Non ho tempo e non mi piace fare visite.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Verrò. Ma se stavi solo perdendo il mio tempo, ti strapperò la lingua!",RandSwear()+"Bene, aspettami. Spero che la tua offerta ne valga la pena. E non pensare nemmeno di giocare brutti scherzi su di me!"),RandPhraseSimple("Accetterò volentieri il tuo invito, capitano.","Mi hai intrigato. Naturalmente, verrò."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Oh, sei malato di mare, vero? Corri a nasconderti sotto la gonna di tua mamma!","Troppo spaventato?! Vattene!"),RandPhraseSimple("Non posso farlo. Se non ti interessa l'oro, è una tua decisione.","È così e non altrimenti. Se non ti va bene - va bene, ci sono molti altri."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ah! Sei coraggioso, vero? Va bene, arrivo!","Vedo che sai rimanere fedele alle tue convinzioni, capitano. Va bene, aspettami."),RandPhraseSimple("Bene, sono d'accordo.","Sei proprio un chiacchierone. Sono pronto a discutere affari sulla tua nave."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ah! Pensavi di attirarmi sulla tua nave e uccidermi lì? Non funzionerà!","Le tue parole non valgono un soldo! Non avrò affari con te!"),"Offerta dubbia. Devo rifiutare.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rum per me! E tu sparisci dalla mia vista!","Non abbiamo già discusso di tutto?"),RandPhraseSimple("Occupati dei tuoi affari. Ho cose da fare.","Non credo che abbiamo nulla di cui discutere."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Ti ho detto che ti avrei aspettato sulla mia nave!";
		link.l1 = "Oh... certo...";
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
			Dialog.Text = RandPhraseSimple("Oh, no, non va bene... Non sono troppe navi per te, "+GetSexPhrase("compagno","ragazza")+"?","Ha! In una compagnia così grande non c'è modo di mantenere i segreti. Vattene.");
			link.l1 = RandPhraseSimple("Come desideri!","Bene. Non che mi importi.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Ottimo. Ora sono certo che non ci sono orecchie sbagliate intorno, e i miei marinai sono già stati informati. Quindi la mia offerta è di acquisire qualche roba senza proprietario.";
//			link.l1 = "E cos'è così difficile? Perché avresti bisogno di me per questo, in primo luogo?";
			Dialog.Text = RandPhraseSimple("Benvenuto a bordo, capitano!","Ottimo. Ora sono certo che non ci sono orecchie indiscrete intorno, e i miei marinai sono già stati informati. Quindi la mia proposta è di acquisire qualche bene senza proprietario.")+"Quindi la mia offerta è di acquisire qualche cosa senza proprietario.";
			link.l1 = RandPhraseSimple("E cosa c'è di così difficile? Perché avresti bisogno di me per questo, in primo luogo?","Senza padrone?! Devi scherzare!");
		}
		else
		{
			Dialog.Text = "Ora sono certo che non ci sono orecchie indiscrete intorno - vai avanti e sputalo fuori!";
			link.l1 = "Quindi la mia offerta è di acquisire qualche cosa senza proprietario.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Ebbene, ci sono persone che lo considerano loro e bisogna convincerli del contrario.","Certo, qualcuno dovrà essere ucciso - ma certamente questo non sarà un problema, vero?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Alla faccenda!","Quell'odore di strage! E dove sono?"),RandPhraseSimple("Vorrei conoscere più dettagli sulla vostra offerta.","Cosa mi stai offrendo esattamente?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Mi stai prendendo in giro. Non parteciperò a questo!","Sembra facile, ma non mi fido di te! Vuoi che tiri le castagne dal fuoco per te? Beh, non sono d'accordo!"),RandPhraseSimple("Sembra promettente, ma passo.","No, non rubo, preferisco quando mi fanno dei regali."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "E cosa c'è di così difficile? Perché avresti bisogno di me per questo, in primo luogo?";
			link.l1 = "Ebbene, ci sono persone che lo considerano loro e bisogna convincerli del contrario.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
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
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Non tirare per le lunghe, sputa il rospo!","Avevo ragione su di te, cos'altro sai?"),RandPhraseSimple("È molto interessante, per favore continua!","Sono "+GetSexPhrase("tutto","tutto")+" orecchie!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Questo suona come un'affare allettante, ma rifiuto ancora. Non ho bisogno di litigare con "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Una carovana? Senza proprietario?! Dovrebbero esserci mille soldati a proteggerla! No, non va bene. Me ne vado."),RandPhraseSimple("No, non sono in guerra con "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", quindi non sono interessato.","La mia risposta è no! Non intendo rovinare i miei rapporti con "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Quel odore di un massacro! E i dettagli?";
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
//			Dialog.Text = "Abbiamo solo "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"per intercettarli.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" la carovana andrà troppo lontano, e non riusciremo a raggiungerla.","Abbiamo esattamente "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" giorni per ucciderli tutti e prendere il bottino!"),RandPhraseSimple("Abbiamo solo "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" giorni per l'intera operazione a nostra disposizione.","Dovremmo sbrigare, "+PChar.Name+". Abbiamo solo "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("Lo faremo in tempo! Mettiamoci in viaggio oggi.","Non perdiamo tempo, allora. Ordina di salpare oggi.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "È molto interessante, per favore continua.";
			link.l1 = "Abbiamo solo "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" per intercettarli.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Non perdiamo tempo! Andiamo!";
		link.l1 = "Andiamo!";
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
		Dialog.Text = RandSwear()+"Mi hai deluso, capitano. Pensavi che ti avrei invitato per "+RandPhraseSimple("Messa della domenica?!!","un gioco per bambini!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Questo è affar tuo. E spetta a me decidere.","Non sto per essere impiccato per un paio di pesos."),RandPhraseSimple("La mia decisione è definitiva, capitano.","Non abbiamo più nulla da discutere."));
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
		Dialog.Text = PCharRepPhrase("Oh, dai! Tutto procederà senza problemi, e nessuno saprà nulla. Uccideremo tutti."),RandPhraseSimple("Dove stai andando, capitano? Forse dalle autorità?","È molto imprudente entrare nella tana di una tigre pensando che sarà facile uscirne."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Vai a baciare il diavolo del mare! Io sono il capitano "+GetFullName(PChar)+" e non mi importa di te! Me ne sto andando!","Giuro per il diavolo, mi stai davvero facendo impazzire!"),RandPhraseSimple("La tua proposta non mi interessa, e non c'è altro di cui discutere. Addio.","Credo che non ci sia più nulla da discutere tra di noi. Scusa, sono occupato e devo andare."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Prendi "+GetSexPhrase("lui","lei")+"! Lega "+GetSexPhrase("lui","lei")+" alla cannoniera! Vediamo di che colore "+GetSexPhrase("suo","lei")+" coraggio ce l'ho!!!","Ehi! Johnny! Henderson! Afferra quello "+GetSexPhrase("birbante","ragazza")+"! Non lasciare "+GetSexPhrase("lui","lei")+" per raggiungere la scialuppa di salvataggio!!!"),RandPhraseSimple("Un peccato, capitano! Spero che il nostro deposito ti piaccia, però. E poi decideremo cosa fare di te.","Gli schiavi bianchi non sono noti per vivere a lungo, capitano, quindi fai la tua scelta: o Hends ti spara in testa, o passi il resto della tua vita in una cava."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ti farò mangiare le tue viscere immonde, "+GetFullName(NPChar)+"!!!","Datevi da parte! Canaglie! Vi ucciderò dove state!"),RandPhraseSimple("La tua offerta è inaccettabile... E decisamente imprudente!!!","Non sei così ospitale, da quel che vedo... Fai spazio!!!"));
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

//		Dialog.Text = "Allora, "+GetFullName(PChar)+", vedo che ho commesso un errore a mescolarmi con te. Ora per noi non c'è bottino. Addio!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Cazzo! Siamo in ritardo - e tutto a causa di quegli stupidi pigri! Ora non c'è bottino da condividere con te, "+GetFullName(PChar)+". Issa la trinchetta! Ci stiamo tirando fuori da qui! ","Allora, "+GetFullName(PChar)+", vedo che ho commesso un errore mischiandomi con te. Ora non c'è bottino per noi. Addio!"),RandPhraseSimple("Sono spariti - e tutto a causa del tuo ritardo! Ora stiamo andando per strade diverse, "+GetFullName(PChar)+".","Non c'è modo che possiamo inseguire il convoglio ora. Ho commesso un errore a coinvolgermi con te. Addio!"))link.l1 = PCharRepPhrase(RandPhraseSimple("All'inferno con quel convoglio! I pescatori di perle sono ancora migliori, e non c'è alcun rischio!","La fortuna è con noi e domani è un altro giorno! Ci sono un sacco di miseri mercanti nei mari che aspettano solo che noi prendiamo i loro soldi!"),RandPhraseSimple("Peccato davvero, che un'operazione così brillante si sia rivelata un totale fallimento! Addio!","L'uomo propone e Dio dispone... Addio!"));
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
//			Dialog.Text = "Oh, perché diavolo mi sono mescolato con te. Hai rovinato tutto. Quindi, ora devi pagarmi una penale di "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Sanguinario "+GetSexPhrase("birbante","sporcizia")+"! Tutto è andato dritto al diavolo del mare!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos sul chiodo, e sparisci dalla mia vista!","Ti sei immaginato di essere ammiraglio Nelson? Hai affondato tutto il bottino, "+GetSexPhrase("idiota","donna sciocca")+"! Dammi ora "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos e sparisci!"),RandPhraseSimple("Hai deciso di scatenare la guerra qui! Questo è assolutamente inaccettabile! Ma, suppongo, possiamo dimenticarci di tutto, se ci paghi "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos.","I tuoi metodi sono completamente inaccettabili! Hai rovinato tutto l'affare! Pagaci immediatamente la nostra parte dell'importo di "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos e vai dove preferisci!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Se non fosse per me, ora saresti pasto per i granchi, maledetto avido!","Certo, avrei dovuto lasciare che la loro nave ammiraglia ti salisse a bordo - allora non avresti avvelenato l'aria ora, dondolando sul pennone!"),RandPhraseSimple("Le tue pretese sono fuori luogo, e le tue insinuazioni sono offensive!","Non abbiamo concordato sulla penalità, quindi non ti sto pagando nulla!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Non posso darti battaglia adesso, e lo sai! Ingoia i tuoi pesos!"," pesos?!! Beh, la Signora Fortuna di certo non mi sorride oggi. Accetto."),RandPhraseSimple("Le tue richieste sono oltraggiose, ma credo di non avere scelta.","I vostri appetiti sono eccessivi, ma devo concordare!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Oh, perché diavolo mi sono mescolato con te. Hai rovinato tutto.";
			link.l1 = "Oh, dai! Hai visto con i tuoi occhi che non c'era altra via.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Allora, il nostro bottino compone "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Andiamo a dividerci.";
			Dialog.Text = PCharRepPhrase("È stato un affare d'oro! Quindi, il nostro bottino compone "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Ottimo lavoro, capitano! Il nostro bottino compone "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" La mia parte è "," La quota della mia nave - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" La tua quota è ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Tutto è corretto! Le barche stanno già venendo caricate!","Sì, tutto è corretto. Un accordo è un accordo."),RandPhraseSimple("Le tue calcolazioni sono corrette. Sono d'accordo.","Quando si tratta di dividere, sei irreprensibile."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Osi pretendere la tua parte? Dovresti essere impiccato all'albero maestro subito!","La tua parte? Qui ognuno per sé. Se non è rimasto nulla per te, è un tuo problema!"),RandPhraseSimple("Non credo che tu possa aspettarti una parte.","La mia risposta è no! Non condivido con canaglie come te!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bene, allora, non ho intenzione di discutere! Addio!","Non versiamo sangue e peggioriamo ancora di più le cose! La prossima volta avremo più fortuna!"),RandPhraseSimple("Ebbene, addio, capitano, non sono nella posizione di fare richieste...","Le perdite e i danni alla mia nave non mi permettono di insistere su una decisione giusta. Lo lascio alla tua coscienza, capitano!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Vento favorevole a te!","Sette piedi sotto la chiglia!"),RandPhraseSimple("Addio! Spero che l'aria fresca del mare ti faccia bene!","Spero che le nostre sfortune non ti rendano ancora più insopportabile, capitano! Addio!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Non l'hai capito! Potresti comprare la tua vita invece! Afferra quel bastardo!","O pensi che stiamo giocando con te? Beh, una volta che ti abbiamo fatto la carena, dovresti diventare più accomodante!"),RandPhraseSimple("Dovremmo accorciare la tua vita, allora, capitano! Se non vuoi andartene in modo amichevole, presto incontrerai San Martino!","Mi lasci senza scelta, "+GetFullName(PChar)+"! Prenderò ciò che è mio, che ti piaccia o no!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Giuro al diavolo, pagherai per questo!!!","Yo-ho! Allora vieni a prendermi, capitano "+GetFullName(PChar)+"! "),RandPhraseSimple("La ferita sarà lunga e profonda!","Preferisci morire velocemente o con un po' di sofferenza?"));
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
		Dialog.Text = "Non voglio avere più a che fare con te!";
		link.l1 = "Nessun problema.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "È stato un piacere fare affari con te. Buona fortuna.";
		link.l1 = "E lo stesso a te.";
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
		Dialog.Text = PCharRepPhrase("È stato un vero massacro! Peccato che non ci fossero ragazze con loro! Il bottino compensa "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Non male, capitano! Il bottino compensa "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" La mia quota è ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" La tua quota è ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Assolutamente giusto, dannazione!","Tutto è perfettamente a posto, accidenti!"),RandPhraseSimple("Le tue calcolazioni sono corrette. Sono d'accordo.","Quando si tratta di dividere, sei irreprensibile."));
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
