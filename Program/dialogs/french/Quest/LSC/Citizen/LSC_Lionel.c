// Лайонел Маскетт - мещанин
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
				dialog.text = "Salut, "+GetAddress_Form(NPChar)+"Êtes-vous un nouveau venu ici ?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Oui, je le suis.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Tu veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Voulez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu te portes. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mon nom est Lionell. Enchanté de vous rencontrer. Comment êtes-vous arrivé ici ?";
			link.l1 = "Sur une barque... J'ai entendu dire qu'il y a une base de contrebandiers et j'ai décidé de l'explorer... Explorée. La barque est coulée et je suis ici.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Considèrent-ils vraiment l'île comme une base de contrebandiers ?";
			link.l1 = "Eh bien, pas officiellement. La majorité ne croit même pas en votre existence.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Sérieusement... Et pourquoi le feraient-ils ? Nous n'existons pas réellement. Tu ne peux pas quitter cet endroit. Bien qu'on dise qu'il y avait une connexion avec Cuba... Mais je ne m'en souviens pas et je vis ici depuis presque huit ans.";
			link.l1 = "Je vois. Ce fut un plaisir de parler avec vous. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire?","Quelque chose de nouveau s'est-il passé sur l'île ?","Me raconteras-tu les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je suis à l'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Souhaiteriez-vous retourner sur le continent ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Et que font les gens ici, sur l'Île Justice ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Et où trouves-tu tout ici ? Nourriture, étoffe, boissons ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "C'est une histoire étrange. Cette île est le seul endroit de tous les Caraïbes que j'ai vu. Quand les choses ont mal tourné pour moi, j'ai embarqué sur un navire marchand depuis la vieille Angleterre. J'allais chercher un travail à Belize, pour être commis au bureau du port. Mais nous n'avons jamais atteint Belize\nJe ne suis pas marin, donc je ne connais pas les détails. Une tempête est survenue et le lendemain notre navire a été détruit par les récifs. Je n'oublierai jamais ce terrible choc, les cris\nQuelqu'un a crié qu'il y avait un trou dans la coque, les gens ont commencé à sauter par-dessus bord. Moi... je ne sais pas nager. Alors je suis resté. Ironiquement, cela m'a sauvé la vie. Le navire a survécu et la tempête s'est calmée à l'aube\nJ'ai pris la seule bonne décision avant de quitter le navire. J'ai pris de la nourriture, construit un radeau et navigué à travers une mer paisible jusqu'à l'anneau extérieur. C'est ainsi que j'ai survécu, le seul de tout l'équipage.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "C'était mon seul rêve pendant les deux premières années ici. Mais maintenant... Qu'est-ce qui rend L'Île Justice pire que n'importe quel autre endroit au monde ? Oui, il n'y a pas de champs verts avec des moutons, mais il y a une mer magnifique et un ciel nocturne rempli de belles étoiles. Je suis bien nourri, je porte des vêtements décents, que je ne pouvais pas me permettre en vivant en Angleterre. J'ai beaucoup d'amis\n Non, monsieur, je ne veux pas quitter cet endroit. Qu'est-ce qui m'attend là-bas ? Un travail de bureau sous un patron bruyant pour trois cents pesos par semaine ? Pas question ! J'ai trouvé tout ce que je cherchais ici, je n'ai besoin de rien d'autre.";
			link.l1 = "Je comprends. Content pour vous !";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ce qu'ils aiment le plus. Les clans jouent à la guerre, les pirates vendent des provisions, Axel Yost achète et vend des trucs, Sancho Carpentero sert des boissons et divertit les gens, frère Julian prie, dit la messe et vend des médicaments. Loderdale et Solderra intriguent l'un contre l'autre, l'Abbé aime être gonflé d'orgueil, Jillian et Tanneke rêvent du véritable amour...";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Des navires, mon ami, des navires. L'activité favorite de la majorité est d'explorer les vaisseaux de l'anneau extérieur et d'en récupérer des trésors. Tu peux y trouver de tout, armes, médicaments, épices et rhum. Beaucoup de navires sont encore inexplorés. Le courant marin amène souvent ici une autre victime...";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regardez-moi ça ! À peine ai-je perdu dans mes pensées que vous avez décidé de fouiller dans mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Décidé de fouiller mes coffres? Tu ne t'en sortiras pas comme ça!";
			link.l1 = "Folle fille!";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
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
