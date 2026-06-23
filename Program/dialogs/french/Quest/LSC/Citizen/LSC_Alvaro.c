// Альваро Гомец - капитан
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
				dialog.text = "Je ne veux pas parler avec toi. Tu attaques des civils paisibles sans raison et les provoques en combat. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh, un nouveau visage ! Salutations. Et quand êtes-vous arrivé ? Je ne me souviens d'aucun naufrage récent.";
				link.l1 = TimeGreeting()+", Mon nom est "+GetFullName(pchar)+". Et mon navire a coulé si paisiblement et rapidement que personne ne l'a remarqué. Et je suis arrivé à l'Île rapidement et discrètement aussi. Tout simplement comme ça...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Voulez-vous quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Me raconterez-vous les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu te portes. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Je vois, Oh, j'ai oublié de me présenter. Pardonnez-moi, señor. Je m'appelle Alvaro Gomez et j'étais autrefois capitaine de mon propre brigantin. Eh bien, maintenant mon beau brigantin repose au fond juste derrière l'anneau extérieur... Tant d'eau a coulé sous les ponts depuis. Ah, peu importe. Heureux de faire votre connaissance !";
			link.l1 = "Ravi de vous rencontrer aussi, señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Voulez-vous me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux vous poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je vous écoute, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Tu as dit que tu étais capitaine. Comment as-tu atterri sur l'île?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que pouvez-vous me dire de la vie sur l'île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dis-moi, les habitants vivent-ils ici en paix ou non ? Je ne parle pas des clans, bien sûr.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Et d'où les habitants se procurent-ils des provisions ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Comme tout le monde. La tempête m'a pris, j'ai perdu mon mât et le contrôle de la barre. Le courant nous a emportés et projetés sur les récifs. Mon navire n'a même pas atteint l'anneau extérieur et a été détruit. Seuls quelques hommes ont survécu.";
			link.l1 = "Histoire triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Que puis-je dire ? Nous avons tout ce dont nous avons besoin pour vivre correctement. Bien que parfois, cela devienne vraiment ennuyeux ici. Et cette mélancolie... La première année fut la pire, mais je m'y suis habitué par la suite. Je me sens mal pour ma pauvre femme Sabrina, elle doit être persuadée que je suis mort. J'espère vraiment qu'elle a réussi à se remarier.\nNe sois pas contrarié, tu t'y habitueras. Va à la taverne, au magasin, à l'église, rencontre d'autres gens. Ne va pas chez les Narvals ou les Rivados à moins que ce ne soit vraiment nécessaire, ce sont des enfoirés rusés.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Vrai, querelles et bagarres sont secrètement interdites ici. Si vous battez quelqu'un sans raison valable ou, Dieu nous en garde, tuez, alors vous finirez isolé. Vous pourriez même être jeté par-dessus bord une nuit. Il y a eu quelques bagarreurs avant sur l'Île. Le premier a simplement disparu, le deuxième est mort dans une cellule de Tartarus après des mois passés à l'intérieur. Bien sûr, cela ne signifie pas que vous ne pouvez pas vous protéger. Mais les locaux sont en fait assez pacifiques. Abbott est prétentieux, mais pas agressif. Kassel est un vrai salopard, mais il garde les mains propres. Pratt est un ancien détenu, mais il est inoffensif. Nous avons ici deux anciens officiers de la marine - Loderdale et Solderra. Ils sont arrivés ici après avoir combattu non loin. Ironiquement, tous deux ont survécu pour continuer à faire des plans sanguinaires l'un contre l'autre.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Des cales, bien sûr. Toutes les provisions, récupérées sur d'autres navires, étaient stockées à Saint-Augustin et partagées entre tous jusqu'à ce que les pirates arrivent. Maintenant, ils tiennent l'Île dans leur poing parce qu'ils possèdent les provisions\nBien sûr, nous avons nos propres réserves, donc ça va. Nous chassons aussi les oiseaux et pêchons... Mais la meilleure chasse se termine par la capture d'un crabe géant. Ils ont une viande très savoureuse et nourrissante. Cependant, on ne les voit que sur l'anneau extérieur\nPlonger pour les chasser est trop risqué. Il y a eu quelqu'un d'assez courageux pour les chasser sous l'eau. Un jour, il est devenu une proie lui-même. Personne ne veut chasser les crabes là-bas depuis.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! Dès que je me perds dans mes pensées, tu décides de fouiller dans mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Cela me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","Bien sûr.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demanderais de rengainer ta lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","Quoi qu'il en soit.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je peux devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
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
