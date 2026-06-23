// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Je ne veux pas parler avec toi. Tu attaques des civils paisibles sans raison et les provoques à se battre. Va-t'en!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, bonjour... Que veux-tu, ami?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+". Et je voulais juste savoir qui vous êtes. Voyez-vous, je viens d'arriver, je me promène dans la ville et je parle avec les gens.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Que veux-tu cette fois ?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, on dit que tu connais bien l'histoire de l'Île Justice. J'ai une question à te poser à ce sujet.";
					link.l4.go = "dolly";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Voulez-vous quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Y a-t-il du nouveau sur l'île ?","Veux-tu me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Splendide. Et tu t'en sortiras bien, car nous sommes tous une grande famille ici. Sauf pour les Narvals et les sales Rivados bien sûr. Mon nom est Antonio, Antonio Betancourt. Je suis le petit-fils de Francisco Betancourt au cas où ce nom te dirait quelque chose.";
			link.l1 = "Francisco Betancourt? J'ai déjà entendu ce nom... Ah, bien sûr ! Dios m'en a parlé et j'ai lu à son sujet dans les notes d'Alvarado...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Je n'ai aucune idée de qui est ce Dios dont vous parlez, mais le capitaine Alvarado nous a rendu visite il y a longtemps. Je l'ai vu personnellement quand j'étais enfant. Il a quitté l'île et a écrit à ce sujet dans ses manuscrits. Et Francisco Betancourt était un amiral espagnol, commandant d'une escadre militaire.\nIl a commencé l'histoire de cet endroit en raison du fait que tous les Rivaos sont des descendants d'esclaves noirs du Tartarus, le navire amiral de l'escadre. Les Narvals sont les enfants des premiers colons blancs, membres d'équipage du Tartarus, du San Augustine et du San Geronimo.";
			link.l1 = "Incroyable ! Alors, es-tu né ici ?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Exactement. Je suis le rejeton direct d'un homme qui a essentiellement occupé l'Île.";
			link.l1 = "Je vois. Enchanté de te rencontrer, Antonio. À bientôt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Bien sûr, ami, demande-moi. Je répondrai à tes questions, bien entendu, mais seulement si je connais les réponses.";
			link.l1 = "Dis-moi, te souviens-tu de l'époque où le galion San Geronimo était encore ici ?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Bien sûr, je m'en souviens. C'était un navire très spécial. Il y avait une statue indienne intéressante et ces païens immondes des Rivados effectuaient des offrandes sacrificielles.";
			link.l1 = "Et comment faisaient-ils cela ? Enlevaient-ils le coeur des gens comme les Mayas ? Ou bien coupaient-ils les têtes ?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "Non... C'était une statue très spéciale - elle attirait les victimes en elle et elles disparaissaient à jamais. L'outil du diable... Dieu merci, elle a coulé avec le navire et ne fera plus jamais de mal. Il est assez intéressant que les sacrifices aient toujours été faits à la même heure le matin. La statue se transformait en or sous la lumière du soleil levant. C'était alors que les sauvages apportaient des victimes, principalement les Narvals qu'ils capturaient.";
			link.l1 = "Intéressant ! Quelqu'un a-t-il déjà essayé d'explorer comment fonctionne la statue ?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Bien sûr que non ! D'abord, les Rivados ne laissent personne d'autre qu'eux-mêmes s'approcher de San Geronimo et, deuxièmement, un honnête catholique doit garder ses distances des actions du diable.";
			link.l1 = "Compris. Je vois que vous n'aimez pas les Rivados. Ai-je raison ?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Vraiment? Je hais ces païens sales! Au cas où tu ne le saurais pas, mon grand-père était le capitaine du navire où les Nègres avec leur chef Rivados se sont mutinés. Laisser leur soi-disant chef pourrir dans la cale était la bonne chose à faire. J'avais aussi une clé magnifique du trésor de Sainte-Anne\nPersonne ne sait où trouver le trésor, peut-être qu'il repose au fond de la mer entouré de crabes, mais la clé était un doux souvenir pour moi et pourtant elle a été volée! Je suis sûr que ce sont les Noirs qui l'ont fait. Ils doivent essayer de trouver le trésor. Je doute qu'ils y parviennent, cela fait trop longtemps, ha-ha! Vermine...";
			link.l1 = "Je vois. Merci pour votre histoire intéressante !";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Vous êtes le bienvenu, je suis toujours ravi de discuter !";
			link.l1 = "Adieu !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je t'écoute, camarade.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Alors, tu n'as rien vu d'autre que l'Île dans ta vie ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Tu es né ici... Et pourquoi n'es-tu pas membre du clan Narval ? Je pensais que tous les autochtones blancs étaient des Narvals...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Et que fais-tu sur l'Île Justice ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dis-moi, as-tu déjà eu envie de quitter l'Île Justice pour un temps ? Voir le monde...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Il semble que oui, en effet. Mais ne crois pas que je suis un idiot ou borné. J'ai hérité d'une belle bibliothèque de mon grand-père et mon père m'a fourni une excellente éducation. Je connais l'histoire ancienne, la géographie, l'astronomie, je parle anglais, français, espagnol et même latin.\nBeaucoup de marins qui ont navigué partout en savent moins que moi. Même si je n'ai rien vu d'autre que ces épaves, j'ai visité mentalement l'Europe, la Chine et l'Inde...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ce n'est pas vrai, bien que tu aies raison à quatre-vingt-dix pour cent. Mais je ne suis pas Narval et je ne veux pas devenir l'un d'eux. Dans quel but ? Monter la garde pendant des heures comme un imbécile ou se battre avec les Rivados ? Pas question, épargne-moi cela. Je suis différent. Je préfère vivre indépendamment et lire des livres.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Mon père m'a laissé un héritage décent et je le dépense avec soin. Donc, je n'ai pas besoin de rôder autour des épaves de vieux navires pour trouver des bijoux à échanger contre de la nourriture. Je ne crois pas aux grands trésors à l'intérieur des vieux navires\nLe seul trésor que je connais est le trésor de Sainte-Anne. C'est un grand coffre en fer. Mais personne n'a encore réussi à le trouver\nDe plus, je vais écrire une histoire détaillée de l'Île basée sur les récits locaux. Que penses-tu - devrais-je essayer ?";
			link.l1 = "J'en suis sûr. Je connais au moins un homme dans l'Archipel qui paierait beaucoup d'or pour un tel livre. Alors c'est votre chance...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Parfois, j'y pense. Peut-être que si un navire capable de braver le courant et de survivre aux tempêtes venait ici, je prendrais le risque. J'ai vraiment hâte de voir les choses si fascinantes décrites dans mes livres ! Mais ce ne sont que des rêves pour l'instant...";
			link.l1 = "Les rêves deviennent réalité. Il suffit d’y croire...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Qu'est-ce que tu fais là, hein? Voleur!","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé d'examiner ma malle !","Tu as décidé de fouiller dans mes coffres? Tu ne t'en tireras pas comme ça!");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !";
			link.l1 = "Folle fille !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Vous savez, courir avec une lame n'est pas toléré ici. Rangez-la.","Écoute, ne joue pas au chevalier médiéval avec ton épée à la main. Range-la, ça ne te sied point...");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous le souhaitez...","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demanderais de rengainer ton épée.","Écoutez, je suis citoyen de la ville et je vous demanderais de baisser votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","Comme vous voulez...","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, camarade, en courant avec une arme. Je peux devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
