// Оеларт Котеел - канонир
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonne journée, monsieur ! Aimez-vous le temps ?";
				link.l1 = TimeGreeting()+". Je me sens bien par n'importe quel temps sauf les tempêtes en haute mer...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Tu veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il  eu  du nouveau  sur l'île ?","Me raconteras-tu les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu te portes. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Faites-moi confiance, je ressens la même chose. Je ne vous ai jamais vu auparavant... mon nom est Oelart Koteel et j'étais maître canonnier sur le navire de guerre hollandais.";
			link.l1 = ""+GetFullName(pchar)+"Oui, je suis un nouveau venu ici. En fait, je viens d'arriver.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Je suis également un novice, je suis ici depuis moins d'un an. Et j'espère vraiment que je ne resterai pas ici trop longtemps, bien que tout le monde essaie de me convaincre du contraire. Enchanté de te rencontrer !";
			link.l1 = "Ravi de vous rencontrer aussi, "+npchar.name+"... ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire?","A-t-il    eu du   nouveau sur l'île ?","Veux-tu me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je vous écoute.";
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
				link.l3 = "As-tu déjà pensé à comment l'Île s'est formée ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "As-tu déjà visité les navires du clan ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Fort banal. Nous avons combattu une goélette anglaise et avons presque gagné la bataille. Ils ont pris la fuite, alors nous les avons poursuivis. Un jour passa, nous étions près de les attraper mais ils ont abattu notre grand mât et, bien sûr, ont réussi à s'échapper.\nQuant à nous, nous avons failli être coulés par une forte bourrasque, puis nous avons été emportés par un courant et finalement notre navire a été jeté sur un récif près de l'anneau extérieur. Très peu ont réussi à survivre...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "C'est mon rêve. Tu ne peux pas imaginer à quel point je me suis ennuyé de cet endroit. Mais comment puis-je le quitter ? Je n'en ai aucune idée. Il n'y a pas de navires ici et il n'y a aucune possibilité d'en construire un nouveau. Ce serait un suicide de naviguer sur un petit bateau.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Selon les navires, elle a environ cent ans. Mais il est possible qu'elle soit plus ancienne, à cause de l'anneau extérieur. Il est fait de navires de haut en bas, peut-être que les plus anciens vaisseaux sont profondément sous l'eau\nQuant à la formation de l'Île... Je crois que les courants et les tempêtes ont amené ici des navires mourants, de sorte qu'un banc de sable artificiel a été créé. L'anneau extérieur a été construit dessus\nLes navires intérieurs sur lesquels nous vivons... soit ils étaient les tout premiers, soit ils ont réussi à traverser l'anneau extérieur. C'est tout à fait possible, l'Amiral et ses pirates nous ont atteints sur leur brig après tout.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "J'ai visité les Rivados. Black Eddy avait besoin d'une consultation sur les canons de navire et je n'ai aucune idée pourquoi. Alors, un des gars des Rivados m'a trouvé et m'a donné le mot de passe. J'ai visité leur 'Protecteur' et 'Velasco'. Les gardes sont coriaces, alors n'essayez même pas de les contourner sans mot de passe.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! A peine ai-je perdu dans mes pensées, que tu as décidé de fouiller ma poitrine !","Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Cela me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoute, je suis citoyen de la ville et je te demanderais de ranger ton épée.","Ecoute, je suis citoyen de la ville et je te demanderais de rengainer ton épée.");
				link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous dites...");
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
