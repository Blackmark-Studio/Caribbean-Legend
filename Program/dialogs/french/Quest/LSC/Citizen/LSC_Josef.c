// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Bonne journée, monsieur. Je suis heureux de rencontrer un homme noble ici.";
				link.l1 = TimeGreeting()+"En fait, j'ai été si proche des gens du commun pendant mon séjour à l'Archipel que j'ai commencé à oublier ma noblesse...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+" ! Heureux de vous rencontrer ! Que direz-vous ? ";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il eu du nouveau sur l'île ?","Me raconteras-tu les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ah, et vous êtes même modeste ! Un véritable gentilhomme ! Je pense que nous serons amis, vous n'êtes pas comme ce pompeux Abbé... Permettez-moi de me présenter - Josef Loderdale, ancien capitaine de la flotte navale anglaise.";
			link.l1 = "Ravi de vous rencontrer. "+GetFullName(pchar)+"à votre service !";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "C'est assez ennuyeux de vivre ici, alors viens à la taverne ce soir, nous pourrons prendre un verre de vin et avoir une conversation intéressante...";
			link.l1 = "Je garderai cela à l'esprit, monsieur. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Pourrais-tu me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ce serait un plaisir de répondre à vos questions, monsieur...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Quel genre de service puis-je obtenir ici ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "En tant qu'officier militaire, quel est votre avis sur la domination des pirates ici ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "J'ai vu beaucoup de coffres verrouillés ici, sur l'Île. Les gens ne se font pas confiance, n'est-ce pas ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Faisant mes devoirs militaires. Je combattais une goélette de guerre espagnole, nous croyions que c'était le navire responsable du pillage des marchands anglais. Le combat fut long, nous les avions presque eus, mais la tempête soudaine a bouleversé la donne. En conséquence, les deux navires ont fait naufrage près des anneaux extérieurs\nLa fortune a un sens de l'humour, moi et le capitaine espagnol avons survécu. Peut-être l'avez-vous déjà rencontré ici. Il s'appelle Lorenzo Solderra, une rare ordure. Soyez prudent avec lui.";
			link.l1 = "Compris. Je prendrai en compte votre avertissement...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Si tu as besoin de te reposer - rends-toi à la taverne de Sancho. Il te fournira toujours de la nourriture, des boissons et un lit. Si tu veux te procurer de la poudre, des munitions, des armes et d'autres choses - va voir Axel Yost, il possède la boutique locale. Les médicaments peuvent être achetés chez frère Julian, il vend aussi des objets sacrés dans son église\nLes Narvals ont un forgeron très talentueux, nommé Schmidt. On dit qu'il forge d'excellentes lames. Il y a aussi un autre artisan talentueux parmi les Narvals, mais je n'ai pas réussi à en savoir plus sur lui\n Et si tu as des ennuis avec des pirates ou des clans, va voir Giuseppe Fazio, c'est le bon spécialiste pour ce genre d'affaires.";
			link.l1 = "Merci pour l'information !";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Je ne peux pas dire que cela me plaît, mais je ne peux rien y faire. J'admets qu'il n'a fallu que quelques jours aux pirates pour faire la paix et établir l'ordre sur l'Île. Avant l'arrivée des pirates, les clans se battaient régulièrement et les gens ordinaires souffraient le plus.\nEn outre, ils vendent la nourriture de manière très soignée et équitable - les citoyens l'obtiennent pour un prix très modique, on ne peut pas en dire autant des clans, les pirates les écorchent vifs en guise de vengeance pour avoir déclenché une guerre.\nJe connais un homme très intelligent parmi les pirates, il s'appelle Layton Dexter. C'est lui qui s'occupe du commerce. J'ai eu une conversation avec lui une fois, je me demande comment un homme aussi talentueux et bien éduqué, qui connaît la tactique, la cartographie et le commerce, a pu rejoindre les pirates.\nIl n'a fallu que quelques jours pour qu'il fasse une excellente carte de l'Île. Je l'ai vue, elle contient presque tout. Je crois qu'il l'a faite pour une guerre possible contre les clans...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "C'est la chose à faire. Ils disent qu'il y a longtemps, le vol était une chose normale sur l'Île jusqu'à ce que tous les coffres aient de nouvelles serrures. Et pourtant, il y a encore quelqu'un qui peut crocheter les coffres. Bien qu'il ne vole que du rhum et des bijoux bon marché, il n'a jamais pris d'or ou d'argent\nToutes les serrures sont uniques, aucune clé identique n'existe - Jurgen Schmidt s'en est assuré. Il fabrique non seulement des lames mais aussi des serrures et des clés. On m'a dit que les coffres extérieurs ne contiennent pas d'objets de valeur, les objets sérieux sont toujours gardés à l'intérieur des navires.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que j'étais perdu dans mes pensées, tu as décidé de fouiller dans mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Décidé d'inspecter mes coffres ? Tu ne t'en sortiras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Vous savez, courir avec une lame n'est pas toléré ici. Rangez-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","Comme tu veux...","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre épée.","Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","Comme tu le souhaites...","Comme vous dites...");
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
