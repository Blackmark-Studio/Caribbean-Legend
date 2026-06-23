// Куранай - индеец
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et tu les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Que veut le frère blanc ?";
				link.l1 = TimeGreeting()+"Frère blanc ? Dis-moi, pourquoi vous, les Indiens, nous appelez soit frères blancs, soit chiens à la face pâle, hein ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vous voulez quelque chose ? ";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Y a-t-il quelque chose de nouveau qui s'est passé sur l'île ?","Voudriez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Montre ce que tu as pu trouver. Peut-être que j'achèterai quelque chose...";
					link.l3.go = "trade";
				}
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Nous vivons tous en paix ici, frère blanc. Curanai n'appelle pas frère blanc le chien à face pâle. Tous les faces pâles ne sont pas des chiens. Je peux appeler beaucoup d'Indiens les chiens à peau rouge.";
			link.l1 = "Hm. Je suppose que vous êtes philosophe...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Les Curanai ne te comprennent pas, frère blanc. Que signifie philosophe ?";
			link.l1 = "Peu importe, frère peau-rouge. J'aime juste ta façon de penser. Tu dis que ton nom est Curanai ? Mon nom est "+GetFullName(pchar)+"Ravi de vous rencontrer.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai content de connaître le nom du frère blanc.";
			link.l1 = "Bien. À plus tard !";
			link.l1.go = "exit";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Demande, frère au visage pâle, Curanai répond.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment êtes-vous arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que fais-tu sur l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Veux-tu rentrer chez toi ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vis-tu paisiblement sur l'Île ? Des combats ou des querelles surviennent-ils ici ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Moi et plusieurs guerriers de ma tribu décidons de naviguer vers une petite île proche de notre terre, visible par temps clair. Nous avons fait un radeau de bambou et une voile. Mais la tempête nous a pris soudainement et nous a emportés en mer ouverte. Nous ne réalisons pas à quelle vitesse notre terre et l'île ont disparu\nNous avons navigué en mer de nombreuses nuits et jours. Tous mes frères sont morts de soif et de faim. Je suis resté seul - les esprits ont eu pitié de Curanai et ont amené un radeau à cette île. J'ai survécu.";
			link.l1 = "Ouais... Triste histoire.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "La pêche à la curanai. Curanai frappe le poisson avec un harpon. Rarement-rarement frappe un gros crabe. Alors Curanai est heureux - le crabe est savoureux, très savoureux. Une pince suffit pour quelques jours. Et Curanai plonge aussi au fond à un endroit. Pas de gros crabes là-bas. Curanai ramasse pierre jaune, pierre bleue, pierre noire et perle. Grandes et petites. Puis Curanai les vend au visage pâle.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai veut rentrer chez lui. Mais où est ma maison ? Curanai ne sait pas où est son village ni comment y arriver.";
			link.l1 = "Hm. Que puis-je dire...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narval et Rivados se battent souvent l'un contre l'autre. Nous vivons en paix et ne faisons de mal à personne. Parfois les visages pâles boivent de l'eau de feu et jurent mais pas de meurtres. Il y a deux officiers-guerriers, l'un déteste l'autre. Un jour, l'un tuera l'autre. Curanai sait.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé d'examiner ma malle !","Tu as décidé de fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Décidé d'inspecter mes coffres ? Tu ne t'en tireras pas comme ça !";
			link.l1 = "Fille insensée !";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame à la main n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demande de garder votre lame au fourreau.","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre épée.");
				link.l1 = LinkRandPhrase("D'accord.","Peu importe alors.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leurs armes prêtes. Ça me fait peur...");
				link.l1 = RandPhraseSimple("Compris.","Je l'emporte.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
