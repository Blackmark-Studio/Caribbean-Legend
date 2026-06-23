// Орели Бертин - просто жительница
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, monsieur. Que direz-vous ?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+", je suis un novice ici, donc je fais connaissance avec les habitants.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire?","A-t-il eu du nouveau sur l'île ?","Pourriez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Je vois. Mon nom est Orelie Bertine. Comment êtes-vous arrivé ici ?";
			link.l1 = "Disons que je voulais juste voir la mystique L'Île Justice.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Alors, vous devez être l'un de ces fous qui viennent ici de leur plein gré... Eh bien, maintenant vous aurez assez de temps pour voir l'Île et manger à votre faim de sa 'justice'.";
			link.l1 = "Et y a-t-il des problèmes avec la justice selon votre sarcasme ?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Non, tout va bien. Mais pour une raison quelconque, nous devons payer les pirates pour notre nourriture, qui était gratuite pour tous il n'y a pas si longtemps. Et quand les clans commencent à se battre dans notre partie de l'Île, nous sommes censés rester dans les navires pour éviter d'être tirés ou massacrés.\nJe veux dire qu'ils sont autorisés à faire ce qu'ils veulent sur notre territoire, mais nous ne pouvons pas faire de même sur le leur. Mais ça va, plus de soucis...";
			link.l1 = "Je vois. Bien, je suis ravi de te rencontrer. À bientôt !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je t'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Vis-tu ici depuis longtemps?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Y a-t-il quelque chose d'intéressant sur l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Que pensez-vous des clans ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Les pirates te dérangent-ils ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Depuis très longtemps. J'ai déjà perdu le compte. Cela doit faire dix-sept ans... non, peut-être dix-huit... ou est-ce vingt? Quelle est l'année actuelle?";
			link.l1 = "Je vois... Alors, vous êtes un ancien ici ?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Relativement. Je me souviens encore des temps où les boucaniers commerçaient avec nous et où les Narvals les plus téméraires et intelligents naviguaient vers le continent pour échanger des provisions contre des marchandises des cales des navires. Mais il y a beaucoup de gens qui n'ont jamais vu d'autres endroits que seulement l'Île parce qu'ils sont nés ici. Ils ne sont pas seulement des anciens, mais des natifs.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Oui, c'est le cas. Tout est intéressant ici. Promenez-vous et voyez par vous-même. Nagez autour de la partie centrale de l'Île. Visitez une taverne, une boutique et une église. Le problème, c'est que l'intérêt retombera dans une semaine, je peux te le promettre.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Et comment sommes-nous censés penser à ces bandits ? J'essaie de me tenir à l'écart d'eux, c'est tout. Au moins, les Narvals font quelque chose de bien pour l'Île, ils ont parmi eux des artisans très talentueux, mais les Rivados ne sont que des sauvages et des païens. \nIls vivent encore selon leurs lois africaines comme il y a des centaines d'années. Des animaux. La seule chose qu'ils ont apprise est d'utiliser des armes à feu. On dit qu'ils pratiquent des rituels de cannibalisme !";
			link.l1 = "Quel cauchemar...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "La partie où ils nous vendent notre propre nourriture est un peu dérangeante, mais ils ne font aucun mal aux citoyens. En fait, au contraire, ils ont mis les clans en ordre et empêchent toute violence. \nIl y avait un citoyen qui causait des problèmes et brandissait son sabre. Il a même blessé deux autres habitants. Les pirates l'ont emmené au Tartare pour quelques semaines. Maintenant, l'homme est calme et paisible. On ne le voit pas souvent, l'anneau extérieur est sa nouvelle demeure...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur !","Regarde-moi ça ! À peine étais-je perdu dans mes pensées que tu as décidé de fouiller dans ma malle !","Décidé à fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Sacrebleu !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
			link.l1 = "Jeune sotte !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, cela ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","Bien.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoute, je suis citoyen de la ville et je te demanderais de baisser ta lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous le dites...");
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
