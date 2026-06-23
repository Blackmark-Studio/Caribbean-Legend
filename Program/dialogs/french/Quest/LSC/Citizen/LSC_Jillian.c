// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh... bonjour ! Tu m'as fait peur. Tu es arrivé si silencieusement... Que veux-tu ?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Je suis nouveau ici et je fais connaissance avec les gens du coin, et j'ai finalement décidé de venir parler à une si jolie dame comme vous. Quel est votre nom ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Voulez-vous quelque chose ? ";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il du nouveau sur l'île ?","Voudriez-vous me raconter les derniers commérages ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Vous me faites rougir, monsieur, mais c'est mon plaisir de toute façon. Merci pour le compliment. Mon nom est Jillian, Jillian Steiner. Enchantée de vous rencontrer.";
			link.l1 = "Ainsi fais-je, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es-tu nouveau ici ? Et comment es-tu arrivé ici, dis-moi ? As-tu survécu au naufrage ?";
			link.l1 = "Eh bien... quelque chose comme ça. Je naviguais ici sur un barque et j'ai presque passé les récifs mais malheureusement j'ai heurté des débris de navires et mon bateau a coulé. Et j'ai nagé ici tout seul.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ah ! Alors vous êtes venu ici de votre propre gré ? Incroyable !";
			link.l1 = "Oui, je suis aussi fou. J'ai décidé de trouver cette L'Île Justice et je l'ai enfin trouvée. Bien que je ne sache pas comment en sortir maintenant.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Tu es très courageux ou imprudent. Naviguer jusqu'ici sur une barque... Maintenant tu vivras avec nous ici car personne n'a pu quitter cet endroit depuis une décennie.";
			link.l1 = "J'ai encore de l'espoir. Très bien, Jillian, je ne te dérangerai pas. À bientôt !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oui, bien sûr, "+pchar.name+"Je t'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Veux-tu quitter l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Et comment se passe ta journée ? Que fais-tu ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vous dites que vous n'êtes pas mariée... Une si jolie fille n'a-t-elle pas d'admirateurs ici ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Je naviguais depuis l'Angleterre avec mes parents. Nous voulions commencer une nouvelle vie, et... j'ai commencé une nouvelle vie ici. Mes parents sont morts et j'ai à peine survécu. J'ai atteint un navire de l'anneau extérieur et y suis resté inconscient pendant un jour jusqu'à ce qu'un local m'y trouve. J'y serais mort s'il ne m'avait pas trouvé.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Et où aller ? Qui a besoin de moi et où ? Je n'ai ni foyer, ni mari, ni argent. Je n'ai jamais été ailleurs que sur cette Île et dans les bas-fonds de Londres. Il semble que mon destin soit de vivre ici...";
			link.l1 = "En es-tu sûr ?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Je m'occupe principalement d'aider frère Julian à l'église. Je fais aussi quelques petits travaux dans la boutique d'Axel. C'est ainsi que je gagne des pièces. Je suis une fille et je ne peux pas grimper sur les débris de navires à l'anneau extérieur.";
			link.l1 = "Bien sûr...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... il y a des admirateurs, oui, mais cela n'a aucune valeur. Je n'aime aucun d'eux et je ne veux pas vivre avec un homme que je n'aime pas. Les hommes qui me plaisent ne me remarquent pas. Eh bien, je ne suis qu'une pauvre fille ordinaire...";
			link.l1 = "C'est juste le début d'une nouvelle vie pour vous...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé de fouiller dans mon coffre !","Tu as décidé de fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Décidé à fouiller mes coffres? Tu ne t'en sortiras pas comme ça!";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Elle me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, cela ne te convient pas...");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de baisser votre lame.");
				link.l1 = LinkRandPhrase("Bien.","Quoi qu'il en soit.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand les hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
