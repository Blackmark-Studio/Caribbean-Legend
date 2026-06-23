// Гхерад Смиитс - матрос
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et tu les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonne journée, matelot, ha-ha ! Que fais-tu ici ?";
				link.l1 = TimeGreeting()+"  Vous ai-je déjà rencontré ? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire?","Y a-t-il eu du nouveau sur l'île ?","Me raconteras-tu les derniers potins?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Bien sûr, vous ne le savez pas, mais c'est facile à arranger, n'est-ce pas ? Je suis Gerard Smeets, marin, un homme de mer de Rotterdam. Et vous avez l'air d'un maître d'équipage pas moins...";
			link.l1 = "Quelque chose comme ça. Mon nom est "+GetFullName(pchar)+"Enchanté de faire votre connaissance.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Vous ressemblez plus à un armateur ou à un maître de paiement... Vous êtes un homme bien éduqué, sans aucun doute. Ravi de vous rencontrer. Comment êtes-vous arrivé ici ?";
			link.l1 = "J'ai décidé d'explorer une zone inconnue. Les boucaniers de Cuba m'ont dit qu'il y avait quelque chose dans cette région et j'ai décidé d'aller voir...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Es-tu le seul survivant? Où ton navire a-t-il coulé? Près de l'anneau?";
			link.l1 = "Je suis le seul. Et ma tartane repose au fond de la mer, elle n'a même pas atteint l'anneau.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Je vois. Eh bien, tu es coincé ici pour un moment. Va voir Sancho pour prendre du rhum, c'est une bonne action...";
			link.l1 = "Je le ferai. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il eu du nouveau sur l'île ?","Me raconteras-tu les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Bien sûr, l'ami. Je t'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Dis-moi, comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Veux-tu quitter l'Île et retourner à ta vie normale ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Les clans ne vous dérangent-ils pas ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Comment l'île s'est-elle formée, as-tu des idées à ce sujet ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Je suis arrivé ici avec ce coq vaniteux nommé Abbot. Je servais sur son navire. Tu sais quoi ? Des gens comme lui ne devraient jamais poser un pied sur le pont d'un navire car ils portent malheur. Le diable a dû le faire naviguer avec nous.\nNous devions seulement naviguer de la Jamaïque à Belize, simple comme bonjour. Mais le mauvais sort nous a poursuivis : notre maître d'équipage est tombé par-dessus bord, un navigateur a commis une erreur, maudits Espagnols et une tempête pour finir. Et nous voilà.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Je  souhaiterais  savoir,  camarade.  Je  savais  autrefois  mais  pas  maintenant.  La  vie  est  agréable  ici,  plein  de  rhum  et  de  vin,  bonne  nourriture,  pas  beaucoup,  mais  quand  même  mieux  que  cette  merde  que  je  mangeais  sur  les  navires\nDes  bons  gars  vivent  aussi  sur  l'Île.  Il  y  a  des  gens  avec  qui  boire  ou  avec  qui  parler.  J'aime  ça  ici.  Donc  je  ne  suis  même  pas  sûr...  Non,  je  suppose  que  non,  je  ne  veux  pas  partir.  J'avais  l'habitude  d'être  en  colère  et  affamé,  regarde  mon  ventre  maintenant,  ha-ha !";
			link.l1 = "Super ! Je suis content pour toi.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Non, ils ne le font pas. Ne discutez pas avec eux et n'allez pas sur leurs territoires sans permission. Ils n'aiment vraiment pas ça. Les Narvals sont de bons gars, la plupart sont nés ici et n'ont pas vu d'autre vie. Beaucoup d'entre eux sont très habiles, Jurgen Schmidt par exemple. C'est un dieu de la forge !";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Facile comme tarte. Haut-fonds et récifs. L'anneau extérieur est fait de navires de haut en bas. Les navires sont pris dans une tempête, heurtent les récifs ou l'anneau extérieur lui-même. C'est ainsi que l'Île grandit. Bien que je n'aie aucune idée pourquoi les navires intérieurs restent au-dessus de l'eau.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regardez-moi ça ! Dès que j'étais perdu dans mes pensées, vous avez décidé d'examiner ma caisse !","Tu as décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Satané !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Cela me rend nerveux.","Vous savez, courir avec une lame n'est pas toléré ici. Rangez-la.","Ecoute, ne joue pas le chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous le souhaitez...","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de baisser votre lame.","Écoute, je suis citoyen de la ville et je te demanderais de ranger ton épée.");
				link.l1 = LinkRandPhrase("D'accord.","Quoi qu'il en soit.","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
