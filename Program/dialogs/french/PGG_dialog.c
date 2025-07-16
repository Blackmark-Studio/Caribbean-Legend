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
//	Dialog.Text = "Vous voyez un bug... Signalez-le à l'AT, pour la Marine.";
//	link.l1 = "Certainement !";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Eh, va-t'en, veux-tu ! Si tu gâches mon marché, je t'arracherai le coeur !";
			link.l1 = RandPhraseSimple("Oses-tu me menacer, chien ?!","Je te ferai avaler tes mots, coquin !");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, je vois. Les affaires sont les affaires. Bonne chance.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Bon après-midi, mon nom est "+GetFullName(NPChar)+", et le vôtre?";
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
//		link.l1 = "Mon nom est "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Alcool pour tout le monde! Je suis le capitaine "+GetFullName(pchar)+".","Je suis le capitaine du '"+PChar.Ship.Name+" et quelques centaines de vrais diables ! He-he ! Mon nom est "+GetFullName(pchar)+"."),RandPhraseSimple("Permettez-moi de me présenter, messieurs. Je suis le capitaine "+GetFullName(pchar)+".","Nous ne nous sommes pas encore présentés. Je suis le capitaine du '"+PChar.Ship.Name+" sous le drapeau de "+NationNameGenitive(sti(PChar.nation))+". Mon nom est "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Eh bien, tout le monde me connaît ici! Je suis "+GetFullName(NPChar)+". Enchanté de vous rencontrer ! Que puis-je faire pour vous ?";
		link.l1 = RandPhraseSimple("J'ai des affaires avec vous !","Je veux te parler...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Eh bien, tout le monde me connaît ici! Je suis "+GetFullName(NPChar)+", capitaine "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "Que diriez-vous de vous joindre à moi? Deux navires valent mieux qu'un. Nous pouvons faire de bonnes affaires ensemble.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Voudriez-vous servir en tant qu'officier sur mon navire?","Je pense que tu ferais un bon officier sur mon navire. Qu'en dis-tu?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Quêtes.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Duels.";
			link.l8.go = "outraged";
		}
		link.l9 = "Rien.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Eh, dégage, veux-tu ! Si tu gâches mon affaire, je t'arracherai le coeur !";
			link.l1 = RandPhraseSimple("Oses-tu me menacer, chien?!","Je te ferai avaler tes mots, fripouille !");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, je vois. Les affaires sont les affaires. Bonne chance.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Je vous ai déjà tout dit pour aujourd'hui !";
			link.l1 = "Oh, ouais...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("De quoi as-tu besoin"+GetFullName(pchar)+"?","Qui est-ce? Oh, toi... Va-t-en, je ne suis pas d'humeur...");
		link.l1 = RandPhraseSimple("Et si on parlait affaires ?","Je voulais te parler...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Oh, regarde qui est là! C'est "+GetFullName(pchar)+". Des nouvelles?","Comment ça va? Que puis-je faire pour vous?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase("Quelles sont les nouvelles?","Quelles sont les nouvelles de l'archipel?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+"Quelles sont les nouvelles?",PGG_Meet_BadRep[iAns]+"Quelles sont les nouvelles de l'archipel?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Que diriez-vous de vous joindre à moi? Deux navires valent mieux qu'un. Nous pouvons faire de bonnes affaires ensemble.","Vous avez l'air d'un capitaine expérimenté. Voulez-vous naviguer sous mon drapeau?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Oh, malheur à moi... Mon navire a coulé!","Regarde qui est là?! Qu'est-ce qui t'a amené ici? Au fait, j'ai perdu mon navire...");
				link.l3 = RandPhraseSimple("Dommage. Peut-être aurez-vous plus de chance la prochaine fois.","Tu ne dis pas... Eh bien, il est temps pour moi de partir. Au revoir.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Voudriez-vous servir en tant qu'officier sur mon navire?","Je pense que tu ferais un bon officier sur mon navire. Qu'en dis-tu ?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Quelles sont les nouvelles?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Quel vilain museau. Il supplie juste pour une raclée.","Oh, notre 'ami'. Voudriez-vous quelques nouveaux trous dans la poitrine?");
			link.l8.go = "outraged";
		}
		link.l9 = "Rien.";
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
			Dialog.Text = RandPhraseSimple("Je vous ai déjà dit que je ne suis pas intéressé.","Je pensais que nous avions déjà tout discuté.");
			link.l1 = RandPhraseSimple("Comment pourrais-je oublier?","C'est juste. Au revoir.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... peut-être pas. Pas une deuxième fois.","Et tu pensais que je mordrais à cet hameçon deux fois?!");
			link.l1 = RandPhraseSimple("Eh bien, comme tu veux...","D'accord. Au revoir, donc.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Non, je suppose que non.","Non, je suis un capitaine, et je ne veux pas servir en tant qu'officier.");
			link.l1 = RandPhraseSimple("Eh bien, comme tu veux...","D'accord. A bientôt, donc.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Vous avez déjà un ensemble complet.","Je ne pense pas que tu sois prêt à me donner des ordres.");
			link.l1 = RandPhraseSimple("Dommage...","Eh bien, le destin en a décidé autrement.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("C'est juste ce dont j'avais besoin! Nos lames gouteront le sang de nos ennemis! Mais il y a un problème - il me faut toujours "+NPChar.Quest.Officer.Price+" pesos pour rembourser mes dettes.","Tu as l'air d'un vrai vieux loup de mer. Et si tu es prêt à payer "+NPChar.Quest.Officer.Price+" pesos, nous pourrions bien travailler ensemble."),LinkRandPhrase("Votre offre me flatte beaucoup. J'accepterai de travailler pour vous pour une somme plutôt modeste de "+NPChar.Quest.Officer.Price+" pesos.","Hmm... Tu as l'air d'un marin expérimenté. Peut-être, je devrais accepter ton offre si tu es prêt à me payer "+NPChar.Quest.Officer.Price+" pesos.","Je pense que nous travaillerons bien ensemble, capitaine. Juste "+NPChar.Quest.Officer.Price+" pesos, et nous avons un accord."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Hmm... et à quel point êtes-vous qualifié ?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Je pense que vous avez des problèmes d'argent, capitaine.";
			link.l1 = "Oh... en effet.";
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

		Dialog.Text = RandPhraseSimple("Excellent !","Je ne vous ai jamais douté, capitaine.");
		link.l1 = "Ne soyez pas en retard pour le départ.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Un bug, informez les devs";
		link.l1 = "Je le ferai !";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Je vous ai déjà dit que je ne suis pas intéressé.","Je pensais que nous avions déjà tout discuté.");
			link.l1 = RandPhraseSimple("Comment pourrais-je oublier ?","C'est juste. Au revoir.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Naviguer avec vous?! Grandissez un peu d'abord!","Je ne pense pas que cela m'intéresse !");
			link.l1 = RandPhraseSimple("Eh bien, comme vous voulez...","D'accord. Au revoir, alors.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Non, je suppose que non.","Non, merci. Je n'aime pas servir sous quelqu'un.");
			link.l1 = RandPhraseSimple("Eh bien, comme tu veux...","D'accord. Au revoir, alors.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Je t'aime bien ! Tu as décroché un marché ! Déjà, j'entends le tintement des pesos dans nos poches !","Tu es intelligent "+GetSexPhrase("gars","jeune fille")+"... Nous devrions bien travailler ensemble !"),LinkRandPhrase("J'aime votre offre. Je suis d'accord.","C'est intéressant. Tu sais, je pense qu'ensemble nous pouvons faire plus !","Cela devrait être amusant. Vous avez un accord !"));
			link.l1 = RandPhraseSimple("Super! Je t'attendrai à la mer!","Marché conclu! Nous formerons un excellent équipage.");
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
			Dialog.Text = RandPhraseSimple("Je pense que vous avez déjà assez de compagnons.","Vous avez déjà assez de navires - pourquoi en auriez-vous besoin de plus ?");
			link.l1 = "Ouais... Peut-être, tu as raison.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Je m'ennuie de toi!!! Je quitte ton escadron!","Ma patience est finie! Je pars."),RandPhraseSimple("Je suis fatigué de vos escapades, 'amiral'... Permettez-moi de prendre congé.","J'en ai assez de votre commandement et je quitte votre escadron."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("D'accord, perds-toi, alors.","D'accord, allez où vous voulez."),RandPhraseSimple("D'accord. Je ne vais pas te retenir.","C'est votre choix. Je vous souhaite un vent favorable."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Euh... que diriez-vous d'une petite prime ?","Caramba! Oh, diable, peut-être, resterais-tu? Je peux même payer un supplément à tes marins!"),RandPhraseSimple("Je détesterais me séparer de toi... Peut-être, une petite compensation peut régler nos différends?","Que diriez-vous d'augmenter votre salaire ?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Une fois suffit pour moi. Je ne ferai plus confiance à tes promesses !","Vous ne me tenterez pas avec de l'argent ! Ma décision est finale !");
			link.l1 = RandPhraseSimple("D'accord, donc bonne chance à toi.","Alors perds-toi et assure-toi que je ne te reverrai jamais !");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Une prime? D'accord! Une somme de "+NPChar.Quest.Companion.Price+" pesos me conviendront bien.","Eh bien, peut-être, si vous êtes prêt à payer à mon équipage "+NPChar.Quest.Companion.Price+" pesos, je pourrais les persuader de rester."),RandPhraseSimple("D'accord! Je peux rester pour une petite prime de "+NPChar.Quest.Companion.Price+" pesos !",NPChar.Quest.Companion.Price+" satisfera moi et mon équipage pendant un certain temps."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Tu te moques de moi ou quoi?! Va-t'en, maintenant!","Ha ! Je préférerais de loin dépenser cet argent pour quelque chose de plus utile !"),RandPhraseSimple("Oh non. Je ne suis pas si riche!","Adieu. Je vais payer autant."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Excellent! Voici votre prime!","Je n'ai jamais douté, que tout était une question d'argent!"),RandPhraseSimple("Excellent! Heureux que tu restes.","Voici ce que j'ai promis."));
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
		Dialog.Text = "Sélectionnez le modèle !";
		link.l1 = "Modèle de quête 1 - mer.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "SÉLECTIONNÉ! Modèle de quête 1 - terre.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Modèle de quête 1 - mer.";
		link.l1 = "Oh, ouais...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SÉLECTIONNÉ! Modèle de quête 1 - terre.";
		link.l1 = "Oh, ouais...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Je vous ai déjà tout dit!";
			link.l1 = "Oh, ouais...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Quelle affaire ?.. Hic ! Ne vois-tu pas - moi et mes potes, nous passons un bon moment !.. Hic...","Ehh... Pas d'affaires aujourd'hui!");
		link.l1 = "Je vois...";
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
					Dialog.Text = "De quoi parler? Quoique, tu es à temps. Quand il s'agit d'affaires, je suis toujours prêt!";
					link.l1 = "Hmm. De quoi parles-tu?";
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

						Dialog.Text = LinkRandPhrase("...seulement moi et le diable connaissons cet endroit, et le dernier à rester en vie obtiendra tout !..","...et Meinard a répondu : 'Je n'attends pas de quartier de toi et je ne t'en donnerai pas non plus'","...et une fois en pleine mer, alors qu'il était déjà un peu éméché, il a suggéré: 'Faisons-nous un enfer là-bas et voyons qui tient jusqu'au bout'.")+PCharRepPhrase(LinkRandPhrase("Maintenant, il y a un autre pirate !","Messieurs, nous avons un gentleman de fortune à notre table, je suppose?","Je sens la poudre a canon et le sang ! Un flibustier a tribord !"),LinkRandPhrase("Les capitaines décents sont une race rare dans ces eaux.","La noblesse est démodée ces jours-ci.","Oh, voilà un capitaine décent, pas du tout comme vous, gredins! He-he!"));
						link.l1 = "Je ne crie pas, je te dis - il y a une affaire rentable !";
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
		Dialog.Text = "Prudent, prudent ! Oh ! Je te reconnais. Tu es "+GetFullName(PChar)+". J'ai beaucoup entendu parler de vous.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Je suis le capitaine "+GetFullName(pchar)+".","Je suis le capitaine du '"+PChar.Ship.Name+" et quelques centaines de vrais diables ! Ha-ha ! Mon nom est "+GetFullName(pchar)+".")+" Mais je ne me souviens pas de toi.",RandPhraseSimple("Permettez-moi de me présenter, messieurs. Je suis le capitaine "+GetFullName(pchar)+".","Nous ne nous sommes pas encore présentés. Je suis le capitaine du '"+PChar.Ship.Name+" sous le drapeau de "+NationNameGenitive(sti(PChar.nation))+". Mon nom est "+GetFullName(pchar)+".")+" Mais je ne me souviens pas de toi.");
//			link.l1 = "Hmm... et qui êtes-vous ? Je ne me souviens pas de vous.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Salut, "+GetFullName(NPChar)+". Comment va la vie?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Je suis "+GetFullName(NPChar)+", capitaine "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". Le corsaire le plus notoire de toute la Mer Espagnole.",". Juste un marin.");
		link.l1 = "Ouais, maintenant je me souviendrai de toi.";
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
		PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
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
//			Dialog.Text = "J'ai des affaires avec toi, "+GetSexPhrase("camarade","fillette")+". Je sais que je peux te faire confiance, mais je ne peux simplement pas en discuter à la taverne - trop d'oreilles indiscrètes. Je t'attendrai à bord de mon navire. Le nom de ma vieille baignoire est '"+NPChar.Ship.Name+".'";
//			link.l1 = "Crache le morceau maintenant, je n'ai pas de temps pour les visites.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("J'ai une affaire intéressante pour toi et tes coupe-jarrets.","Si nous unissons nos forces, nous pourrions gagner un très gros prix en effet ! Bien sûr, nous devrons tuer quelqu'un dans le processus. Hi-hi."),RandPhraseSimple("J'ai une proposition d'affaires pour vous, capitaine.","Capitaine, votre réputation est sans pareil, et donc je vous propose de participer à une affaire tentante."))+RandPhraseSimple("Juste entre nous deux. Discutons-en dans la cambuse de '"+NPChar.Ship.Name+" au-dessus du tonneau de la meilleure bière. Aujourd'hui.","Nous ne devrions pas en discuter ici, négocions les détails sur '"+NPChar.Ship.Name+" en paix et tranquillité. Et s'il vous plaît, ne prenez pas trop de temps.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Au diable ces retards! Si c'est bon, je veux le savoir tout de suite, et encore plus si c'est mauvais!","Il n'y a aucun interet a de tels fils courts! Il y a une chambre convenable dans la taverne - allons-y!"),RandPhraseSimple("Et pourquoi ne pouvons-nous pas discuter de votre offre tout de suite, dans la salle de la taverne?","Je crains que je n'ai guère envie de visiter votre navire. Si vous avez besoin de quelque chose, crachez le morceau ici et maintenant !"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Nous ne devrions pas discuter affaires dans la taverne - trop d'oreilles indésirables. Je t'attends sur mon navire '"+NPChar.Ship.Name+". Nous parlerons là-bas.";
			link.l1 = "Je n'ai pas de temps et je n'aime pas rendre visite.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Je viendrai. Mais si tu as juste perdu mon temps, je t'arracherai la langue !",RandSwear()+"D'accord, attends-moi. J'espère que ton offre en vaut la peine. Et ne pense même pas à me jouer des tours!"),RandPhraseSimple("J'accepterai volontiers votre invitation, capitaine.","Vous m'avez intrigué. Bien sûr, je viendrai."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Oh, tu as le mal de mer, n'est-ce pas? Cours et cache-toi sous la jupe de ta maman!","Trop peur?! Dégage!"),RandPhraseSimple("Impossible. Si tu ne te soucies pas de l'or, c'est ton choix.","C'est comme ça et pas autrement. Si tu n'en veux pas - très bien, il y en a beaucoup d'autres."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha ! Tu es courageux, n'est-ce pas ? D'accord, je viens !","Je vois que vous pouvez tenir vos armes, capitaine. D'accord, attendez-moi."),RandPhraseSimple("D'accord, je suis d'accord.","Vous parlez beaucoup. Je suis prêt à discuter affaires sur votre navire."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha ! Tu pensais me attirer sur ton navire et me tuer là-bas ? Ça ne marchera pas !","Vos paroles ne valent pas un sou! Je n'aurai aucune affaire avec vous!"),"Offre douteuse. Je dois refuser.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Du rhum pour moi ! Et toi, disparais de ma vue !","N'avons-nous pas déjà tout discuté ?"),RandPhraseSimple("Occupe-toi de tes affaires. J'ai des choses à faire.","Je ne pense pas que nous ayons quelque chose à discuter."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Je t'ai dit que je t'attendrais sur mon navire !";
		link.l1 = "Oh... bien sûr...";
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
			Dialog.Text = RandPhraseSimple("Oh, non, ça ne va pas faire l'affaire... N'est-ce pas trop de navires pour toi, "+GetSexPhrase("camarade","demoiselle")+"?","Ha ! Dans une si grande compagnie il n'y a aucune façon de garder les choses secrètes. Dégage.");
			link.l1 = RandPhraseSimple("Comme vous voulez!","D'accord. Pas que ça me concerne.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Génial. Maintenant, je suis sûr qu'il n'y a pas d'oreilles indiscrètes autour, et mes marins ont déjà été informés. Alors, mon offre est d'acquérir des objets sans propriétaire.";
//			link.l1 = "Et qu'est-ce qui est si difficile à ce sujet ? Pourquoi auriez-vous besoin de moi pour cela, en premier lieu ?";
			Dialog.Text = RandPhraseSimple("Bienvenue à bord, capitaine!","Super. Maintenant, je suis sûr qu'il n'y a pas de mauvaises oreilles aux alentours, et mes matelots ont déjà été informés. Alors, mon offre est d'acquérir des affaires sans maître.")+" Donc, mon offre est d'acquérir des choses sans propriétaire.";
			link.l1 = RandPhraseSimple("Et qu'est-ce qui est si difficile à ce sujet ? Pourquoi auriez-vous besoin de moi pour ça, en premier lieu ?","Sans propriétaire?! Vous devez plaisanter!");
		}
		else
		{
			Dialog.Text = "Maintenant, je suis certain qu'il n'y a pas d'oreilles indiscrètes autour - allez-y et crachez le morceau !";
			link.l1 = "Alors, mon offre est d'acquérir des choses sans propriétaire.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Eh bien, il y a des gens qui le considèrent comme leur propre et ils doivent être convaincus du contraire.","Bien sûr, quelqu'un devra être tué - mais certainement que cela ne va pas être un problème?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Au travail !","Ça sent le massacre! Et où sont-ils?"),RandPhraseSimple("Je voudrais en savoir plus sur votre offre.","Que me proposez-vous exactement ?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Tu me fais marcher. Je ne vais pas participer à ça !","Cela semble facile, mais je ne vous fais pas confiance ! Vous voulez que je retire les marrons du feu pour vous ? Eh bien, je suis en désaccord !"),RandPhraseSimple("Cela semble prometteur, mais je vais passer.","Non, je ne vole pas, j'aime quand ils me donnent des cadeaux à la place."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "Et qu'est-ce qui est si difficile à ce sujet ? Pourquoi auriez-vous besoin de moi pour ça, en premier lieu ?";
			link.l1 = "Eh bien, il y a des gens qui le considèrent comme leur propre et ils doivent être convaincus du contraire.";
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
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Ne traîne pas, crache le morceau !","J'avais raison à ton sujet, que sais-tu d'autre?"),RandPhraseSimple("C'est très intéressant, continuez s'il vous plaît!","Un suis "+GetSexPhrase("tout","tout")+" oreilles!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Cela semble être une affaire tentante, mais je refuse toujours. Je n'ai pas besoin de me quereller avec "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Un convoi? Sans propriétaire?! Il devrait y avoir mille soldats pour le garder! Non, ça ne va pas. Je pars."),RandPhraseSimple("Non, je ne suis pas en guerre avec "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", donc je ne suis pas intéressé.","Ma réponse est non! Je ne vais pas ruiner mes relations avec "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Cela sent le massacre! Qu'en est-il des détails?";
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
//			Dialog.Text = "Nous avons seulement "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" pour les intercepter.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("En "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" le convoi ira trop loin, et nous ne pourrons pas le rattraper.","Nous avons exactement "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" jours pour les tuer tous et obtenir le butin!"),RandPhraseSimple("Nous n'avons que "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" jours pour toute l'operation a notre disposition.","Nous devrions nous dépêcher, "+PChar.Name+". Nous n'avons que "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("Nous le ferons à temps ! Mettons les voiles aujourd'hui.","Allons, ne perdons pas de temps. Ordre de lever l'ancre aujourd'hui.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "C'est très intéressant, continuez s'il vous plaît.";
			link.l1 = "Nous n'avons que "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" pour les intercepter.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Allons-y sans perdre de temps ! En avant !";
		link.l1 = "Nous voila partis !";
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
		Dialog.Text = RandSwear()+"Vous m'avez déçu, capitaine. Pensiez-vous que je vais vous inviter pour "+RandPhraseSimple("Messe du dimanche?!!","un jeu d'enfants !??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("C'est ton affaire. Et c'est à moi de décider.","Je ne vais pas me pendre à la corde pour quelques pesos."),RandPhraseSimple("Ma décision est finale, capitaine.","Nous n'avons plus rien à discuter."));
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
		Dialog.Text = PCharRepPhrase("Oh, allez! Tout se passera en douceur, et personne ne saura rien. Nous tuerons tout le monde."),RandPhraseSimple("Où allez-vous, capitaine ? Aux autorités, peut-être ?","Il est assez imprudent de marcher dans la tanière d'un tigre en pensant que vous pourriez en sortir facilement."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Va embrasser le diable de la mer! Je suis le capitaine "+GetFullName(PChar)+" et je me fiche de toi ! Je m'en vais !","Je jure par le diable, tu me rends vraiment fou !"),RandPhraseSimple("Votre proposition ne m'intéresse pas, et il n'y a rien de plus à discuter. Adieu.","Je pense qu'il n'y a plus rien à discuter entre nous. Désolé, je suis occupé et je dois partir."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Saisir "+GetSexPhrase("lui","elle")+"! Attache "+GetSexPhrase("lui","elle")+" aux canons! Voyons quelle couleur "+GetSexPhrase("son","elle")+" les tripes sont!!!","Hey ! Johnny ! Henderson ! Saisis ça "+GetSexPhrase("canaille","fillette")+"! Ne laisse pas "+GetSexPhrase("lui","elle")+" pour atteindre le canot de sauvetage!!!"),RandPhraseSimple("Dommage, capitaine! J'espère que notre cale vous plaira, cependant. Ensuite, nous déciderons quoi faire avec vous.","Les esclaves blancs ne vivent pas longtemps, capitaine, alors faites votre choix : soit Hends vous tire une balle dans la tête, soit vous passez le reste de votre vie dans une carrière."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Je te ferai manger tes tripes infectes, "+GetFullName(NPChar)+"!!!","Cédez le passage ! Coquins ! Je vous tuerai où vous vous tenez !"),RandPhraseSimple("Votre offre est inacceptable... Et très imprudente!!!","Vous n'êtes pas si hospitalier, comme je peux le voir... Faites place!!!"));
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

//		Dialog.Text = "Alors, "+GetFullName(PChar)+", Je vois que j'ai fait une erreur en me mêlant à toi. Maintenant, il n'y a pas de butin pour nous. Adieu !";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bon sang! Nous sommes en retard - et tout cela à cause de ces imbéciles paresseux! Maintenant, il n'y a pas de butin à partager avec vous, "+GetFullName(PChar)+". Hissez la voile d'étai! Nous nous tirons d'ici! ","Alors, "+GetFullName(PChar)+", Je vois que j'ai fait une erreur en me mêlant à toi. Maintenant, il n'y a pas de butin pour nous. Adieu!"),RandPhraseSimple("Ils ont disparu - et tout à cause de votre retard! Maintenant, nous allons dans des directions différentes, "+GetFullName(PChar)+".","Aucune chance que nous puissions rattraper la caravane maintenant. J'ai fait une erreur en m'impliquant avec toi. Adieu!"))link.l1 = PCharRepPhrase(RandPhraseSimple("Au diable cette caravane! Les plongeurs de perles sont encore meilleurs, et il n'y a aucun risque impliqué!","La chance est avec nous et demain est un autre jour! Il y a plein de marchands pitoyables sur les mers qui attendent juste que nous prenions leur argent!"),RandPhraseSimple("Dommage, en effet, qu'une operation si brillante se soit revelee etre un echec total! Adieu!","L'homme propose et Dieu dispose... Adieu!"));
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
//			Dialog.Text = "Oh, pourquoi diable me suis-je mêlé à toi. Tu as tout gâché. Alors, maintenant tu dois me payer une pénalité de "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Assoiffé de sang "+GetSexPhrase("canaille","ordure")+"! Tout est allé droit vers le diable de mer !"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos sur l'ongle, et sors de ma vue!","Tu t'es pris pour l'amiral Nelson ? T'as coulé tout le trésor, "+GetSexPhrase("imbécile","femme insensée")+"! Donne-moi maintenant "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos et dégage!"),RandPhraseSimple("Vous avez décidé de faire la guerre ici ! C'est complètement inacceptable ! Mais, je suppose, nous pouvons oublier cela, si vous nous payez "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos.","Vos méthodes sont totalement inacceptables ! Vous avez ruiné toute l'affaire ! Payez-nous immédiatement notre part pour un montant de "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos et allez où vous voulez!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Si ce n'était pas pour moi, tu nourrirais les crabes maintenant, sale avare !","Oh oui, j'aurais dû laisser leur navire amiral vous aborder - alors vous n'empoisonneriez pas l'air maintenant, en vous balançant sur le yard !"),RandPhraseSimple("Vos demandes sont déplacées, et vos insinuations sont insultantes !","Nous n'avons pas convenu de la pénalité, donc je ne vous paie rien !"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Je ne peux pas te combattre maintenant, et tu le sais! Étouffe-toi avec tes pesos!"," des pesos?!! Eh bien, Dame Chance ne me sourit certainement pas ce jour-là. Je suis d'accord."),RandPhraseSimple("Vos exigences sont scandaleuses, mais je pense que je n'ai pas le choix.","Vos appétits sont excessifs, mais je dois être d'accord !"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Oh, pourquoi diable me suis-je mêlé à toi. Tu as tout gâché.";
			link.l1 = "Oh, allez! Tu as vu par toi-même qu'il n'y avait pas d'autre moyen.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Alors, notre butin s'élève à "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Partons-nous.";
			Dialog.Text = PCharRepPhrase("C'était une affaire chaude! Alors, notre butin s'élève à "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Excellent travail, capitaine! Notre butin constitue "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" Ma part est "," La part de mon navire - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" Ta part est ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Tout est correct! Les bateaux sont déjà en train d'être chargés!","Oui, tout est correct. Un marché est un marché."),RandPhraseSimple("Vos calculs sont corrects. Je suis d'accord.","Quand il s'agit de partager, tu es irréprochable."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Tu oses demander ta part? Tu devrais être pendu sur le mât tout de suite!","Ta part ? Ici, c'est chacun pour soi. Si rien ne te restait, c'est ton problème !"),RandPhraseSimple("Je ne pense pas que tu peux t'attendre à une part quelconque.","Ma réponse est non! Je ne partage pas avec des canailles comme toi!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Eh bien, d'accord alors, je ne vais pas discuter ! Adieu !","Ne renversons pas de sang et n'aggravons pas les choses ! La prochaine fois, nous aurons plus de chance !"),RandPhraseSimple("Eh bien, adieu, capitaine, je ne suis pas en position de faire des exigences...","Les pertes et les dommages à mon navire ne me permettent pas d'insister sur une décision juste. Je le laisse à votre conscience, capitaine!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Vent favorable à toi !","Sept pieds sous la quille !"),RandPhraseSimple("Adieu! J'espère que l'air frais de la mer te sera bénéfique!","J'espère que nos malheurs ne vous rendent pas encore plus insupportable, capitaine! Adieu!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Ne l'avez-vous pas compris ! Vous pourriez acheter votre vie à la place ! Attrapez le salaud !","Ou tu penses que nous jouons des jeux avec toi ? Eh bien, une fois que nous t'aurons fait passer par-dessus bord, tu devrais devenir plus docile !"),RandPhraseSimple("Nous devrons raccourcir votre vie, alors, capitaine ! Si vous ne partez pas de manière amicale, vous rencontrerez bientôt Saint Martin !","Tu ne me laisses pas le choix, "+GetFullName(PChar)+"! Je prendrai ce qui est à moi, que cela vous plaise ou non !"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Je jure par le diable, tu paieras pour ça!!!","Yo-ho! Alors viens me chercher, capitaine "+GetFullName(PChar)+"! "),RandPhraseSimple("La coupure sera longue et profonde !","Souhaitez-vous mourir rapidement ou avec un peu de souffrance?"));
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
		Dialog.Text = "Je ne veux plus avoir affaire avec toi !";
		link.l1 = "Aucun problème du tout.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "C'est un plaisir de faire affaire avec vous. Bonne chance.";
		link.l1 = "Et pareillement à toi.";
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
		Dialog.Text = PCharRepPhrase("C'était un véritable massacre! Dommage qu'il n'y avait pas de gourgandines avec eux! Le butin compense "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Pas mal, capitaine! Le butin compense "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" Ma part est ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" Ta part est ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Absolument juste, bon sang !","Tout est parfaitement correct, bon sang!"),RandPhraseSimple("Vos calculs sont corrects. Je suis d'accord.","Quand il s'agit de partager, tu es irréprochable."));
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
