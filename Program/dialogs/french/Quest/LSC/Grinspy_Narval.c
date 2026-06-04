// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Quoi? Que veux-tu?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Je voulais rencontrer le chef du clan.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"Veux-tu quelque chose ?";
				link.l5 = "Je voulais juste te saluer. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Maintenant tu me connais. Mon nom est Donald Greenspen et ne mets pas moi ou mes hommes en colère. Et n'essaie pas de visiter le 'San Gabriel' tant que tu n'as pas de mot de passe. La boutique est libre d'accès, tout le monde a besoin de faire du commerce. Des questions ?";
			link.l2 = "Non, j'ai compris. À plus tard.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Quelle affaire avez-vous à me proposer ?";
			link.l1 = "Une affaire très désagréable, Donald. Une tentative d'assassinat a eu lieu contre Steven la nuit dernière. Des combattants de ton clan y ont participé.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Je n'en sais rien. Pourquoi penses-tu qu'ils étaient mes hommes ?";
			link.l1 = "Parce que j'y étais. Nous sommes capables de voir la différence entre vos hommes, les pirates et les Rivados. Le groupe était dirigé par Mary Casper et Chad Kapper. Avez-vous besoin de plus de preuves ?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Je ne peux que vous assurer que mes hommes et moi n'avons rien à voir avec cela.";
			link.l1 = "Tu devras en convaincre l'amiral, et cela ne sera pas aisé. Dodson est très en colère contre tous les Narvals après l'attaque. Il va te déclarer la guerre - il cessera de te fournir des provisions et tirera sur tes hommes dès qu'il en aura l'occasion. Et ce ne sont pas que des mots.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "J'espère que cet amiral comprend ce qu'il va faire. Doute-t-il que mes hommes savent aussi tirer ?";
			link.l1 = "Je crois qu'il le fait. Il est prêt à transformer le 'San Augustine' en forteresse et à se battre jusqu'à ce que vous mouriez tous de faim. De plus, Dodson va parler avec les Rivados et leur proposer une coopération. Vous n'aurez aucune chance contre l'amiral et les Rivados ensemble.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Merde ! Mais nous ne faisons pas partie de cette tentative ! Pourquoi tout le clan doit-il payer pour les actions de cette idiote de Mary et d'une bande de vauriens de mon équipage ?\nEn plus, soyons logiques, en tuant Marlow, Dodson lui-même a provoqué Mary et mes soldats. C'est exactement ce qui se passe quand on commet une telle bassesse.";
			link.l1 = "Tu ne comprends rien. On t'a dupé. Pourquoi es-tu si sûr que Dodson a tué Alan ? En fait, il pense que c'est toi qui l'as fait pour prendre sa place...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Je m'en fous de ce qu'il pense. Toutes les preuves sont contre lui. Seuls lui et ses hommes avaient accès à la prison. Alan était entre ses mains. Mary la Rouge m'a dit bien des choses. Avant qu'Alan ne soit assassiné, Dodson a personnellement visité la prison et il ne le fait pas souvent.";
			link.l1 = "As-tu vu sa mort ?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Balivernes ! Bien sûr que non.";
			link.l1 = "Et Chimiset ont. Oui-oui, le sorcier Rivados qui était assis à côté d'Alan. Il a également été assassiné là récemment. J'étais dans la prison un jour avant sa mort et j'ai eu une conversation avec lui. Milrow a été tué par Chad Kapper, le maître d'équipage du Requin.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Est-ce vrai ?";
			link.l1 = "Pense-y : Chimiset se fichait de ta relation avec l'amiral. Il n'avait aucune raison de mentir. Le vieux sorcier avait peur de Chad, il pensait qu'il serait le prochain. Il avait raison, Chad l'avait assassiné dès qu'il avait appris que l'amiral allait le libérer.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Mais pourquoi Kapper voulait-il la mort d'Alan ?";
			link.l1 = "Sacré bleu, ne comprends-tu vraiment pas ? Je t'ai dit que Kapper travaillait avec Mary la Rouge. Il voulait prendre la place du Requin et a échafaudé un plan rusé pour y parvenir. Tuer Alan Milrow et répandre des rumeurs sur l'implication du Requin dans sa mort a rendu le clan des Narvals hostile envers l'amiral...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Folle fille Mary lui a fait confiance et s'est rangée du côté du véritable meurtrier de son petit ami. Ils avaient persuadé quelques Narvals de les rejoindre, cela a dû être facile pour Mary. Puis ils ont organisé une attaque contre l'amiral dans la cabine de Fazio qui a été forcé d'écrire une invitation à l'amiral...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "J'ai une lettre de Fazio qui explique tout. Chimiset a été tué par Chad en tant que témoin dangereux. Il collaborait avec les Narvals et les Rivados seraient vraiment ravis d'entendre cela lors de leur conversation avec le Requin. Nous prouverons facilement à Black Eddie que Chad est devenu l'un des vôtres en montrant cette lettre.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Vous avez tous les atouts, que faites-vous ici alors ? Vous voulez quelque chose de moi, n'est-ce pas ?";
			link.l1 = "Je le pense. Parce que je crois que tout cela était le plan de Chad et que vous n'êtes pas impliqué. Chad a trompé Mary, elle a appelé ses amis de votre clan à l'aide, c'est toute une histoire. Du moins, je n'ai trouvé aucune preuve contre vous ou tout autre Narval...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Mais cela ne veut pas dire qu'il n'y a pas d'autres comploteurs qui restent. Je veux que tu les cherches. Ensuite, peut-être, nous réglerons les choses sans un massacre.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "Je t'ai déjà dit qu'aucun autre de mes hommes n'en faisait partie. Après la mort de Marlow, Mary a pratiquement quitté le clan et s'est enfermée dans sa cabine. En fait, je n'ai aucune idée de comment elle a réussi à persuader les autres d'y participer, mais il semble qu'elle y soit parvenue. Je jure que ni moi ni personne d'autre de mon clan n'agissons contre l'amiral.\nNous avons perdu trop d'hommes récemment, donc nous ne voulons pas nous engager dans des affaires compliquées maintenant. Je n'ai pas peur de l'attaque de l'amiral, même rejoint par les Rivados. Les Narvals sont de vrais guerriers et nous le prouverons dans notre dernière bataille. Mais cela serait inutile.\nNous avons déjà décidé de maintenir la paix avec l'amiral. Les Rivados sont une autre affaire, nous ne négocions pas avec les Nègres. Je suis prêt à m'excuser personnellement auprès de l'amiral, à demander pardon pour mes soupçons causés par la mort de Milrow et pour l'attaque contre sa vie. Je jurerai sur la Bible pour prouver ma sincérité. Vous et Dodson êtes-vous d'accord avec cela ?";
			link.l1 = "Je le suis. Es-tu sûr qu'il n'y a pas de ruses à attendre de tes hommes ?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Absolument. J'informerai mon clan du véritable meurtrier d'Alan Milrow. La relation de mes hommes avec l'amiral changera immédiatement, je vous l'assure. Dites-moi, un massacre sera-t-il nécessaire après cela ?";
			link.l1 = "Non, cela n'arrivera pas. Je suis ici pour l'empêcher. Je te fais confiance, Donald, et je vais essayer de convaincre Requin. Il me reste quelques arguments... À bientôt, Donald !";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "As-tu déjà parlé à l'amiral? Des résultats?";
			link.l1 = "Je suis en cours. Je te verrai plus tard...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Avez-vous déjà parlé à l'amiral ? Des résultats ?";
			link.l1 = "Oui, je l'ai fait. Vos excuses sont acceptées, l'accusation de votre clan est levée. Il y a même plus, Shark vous propose de venir le voir pour discuter des termes de l'accord de paix futur entre les Narvals et les pirates.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Pour être honnête, je ne m'attendais pas à... C'est une excellente nouvelle. Peut-être pourrons-nous même reconsidérer les prix des provisions pour notre clan et une nouvelle politique concernant les Rivados.";
			link.l1 = "Cela ne concerne que vous et l'amiral.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Oui, bien sûr. Vous avez rendu un grand service au clan des Narvals en empêchant un bain de sang inutile et peut-être même l'anéantissement total de mes hommes. Prenez ce mousquet de tour en signe de ma gratitude, vous ne trouverez pas une autre arme de ce genre\nDe plus, vous êtes autorisé à visiter nos zones restreintes comme n'importe quel membre du clan.";
			link.l1 = "Merci ! Adieu maintenant, j'ai beaucoup de choses à faire.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bonne chance. Viens me voir si tu as des questions.";
			link.l1 = "Compris. À bientôt !";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho ! "+GetFullName(pchar)+"! Tu es... non, c'est impossible ! Es-tu vivant ?!";
				link.l1 = "Les rumeurs sur ma mort étaient quelque peu exagérées, Donald. Ha-ha, ravi de te voir !";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, mon ami "+GetFullName(pchar)+"Besoin de quelque chose ?";
			link.l1 = "Non, je ne le fais pas. Je voulais juste te saluer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Quel affaire as-tu pour moi ?";
			link.l1 = "Une très désagréable, Donald. Il y a eu une tentative d'assassinat sur la vie de Steven. Des combattants de ton clan y ont participé.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Je n'en sais rien. Pourquoi pensez-vous que mes hommes étaient impliqués ?";
			link.l1 = "Parce que j'en ai personnellement tué quelques-uns avec Chad Kapper, le contremaître de l'amiral qui est responsable de tout ce bazar. Il n'a pas pu le faire tout seul, alors vos hommes l'ont beaucoup aidé. L'amiral le sait et il est très, très en colère.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Mes hommes ? Qui exactement, pouvez-vous les nommer ?";
			link.l1 = "Ils ne se sont pas présentés. Ils ne faisaient que tirer et croiser le fer. Vos gens sont imprudents. Ils peuvent attaquer même l'un des leurs. Au diable avec moi ou avec l'amiral, mais tenter de tuer la fille ?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. De qui parlez-vous ?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "De qui je parle ? Je parle de l'attaque sur Mary la Rouge. Deux Narvals ont tenté de la tuer. Je suis arrivé à sa cabine à un moment critique par pur hasard. Ils l'auraient tuée si j'étais arrivé plus tard. Je n'ai pas demandé leurs noms, désolé, je n'ai pas eu le temps de leur parler, mais Mary a dit qu'ils étaient des Narvals.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "De qui je parle ? Je parle de l'attaque sur Mary la Rouge et de ces deux Narvals qui l'ont tuée.";
				link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Quoi ? Pourquoi ne m'a-t-elle pas dit ? J'aurais agi immédiatement !";
			link.l1 = "Elle avait peur de quitter sa cabine récemment. Elle s'est disputée avec vous il n'y a pas longtemps, alors pourquoi devrait-elle courir vers vous et demander votre aide ?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Je n'ai pas eu de dispute avec elle ! Elle exigeait l'impossible de moi, nous avons eu une conversation houleuse et je l'ai renvoyée. Mais cela ne veut pas dire que je...";
			link.l1 = "Très bien, soit. Après tout, tous les problèmes sont résolus maintenant. Mais il y a des salauds parmi vos hommes, c'est un fait.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Quoi ? Elle a été tuée par les Narvals ? Pourquoi ?";
			link.l1 = "Par ordre de Chad Kapper, Donald. Elle en savait trop et elle ne voulait pas aider Chad. Et maintenant, la pauvre fille est morte !";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Je le jure, je n'en savais rien!";
			link.l1 = "Bien sûr, tu ne l’as pas fait... Mais parlons de l’amiral. Chad Kapper avait organisé la tentative et tes hommes l’ont aidé. Ils ont essayé d’empoisonner Dodson et je l’ai à peine empêché.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Je n'ai rien commandé de tel. Dodson sait que je ne soutiens pas la politique du défunt Alan et je pense qu'un maigre compromis vaut mieux qu'un gros procès.";
			link.l1 = "Vous devrez en convaincre l'amiral et cela ne sera pas facile. Dodson est très en colère contre tous les Narvals après la tentative. Il va vous déclarer la guerre.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "J'espère que l'amiral comprend ses actions. Doute-t-il que mes hommes puissent riposter ?";
			link.l1 = "Il le pense. Il croit que ton clan est une bande de brigands et qu'il doit être détruit avant que vous ne commenciez à tuer tout le monde. De plus, nous avons de solides liens avec les Rivados. Je peux simplement parler à Black Eddie et lui proposer une alliance. Vous ne pourrez pas nous résister tous.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Putain ! Pourquoi tout le clan doit-il payer pour les actions de quelques idiots ? Ne pense pas que j'ai peur. Nous sommes des guerriers et nous le prouverons, même lors de notre dernier combat. Mais je veux la justice. En fait, c'est l'amiral qui est responsable de la mort d'Alan Milrow dans la prison.";
			link.l1 = "Comment peux-tu être le chef, Donald... Tu ne sais rien ni sur Mary ni sur Alan. Chad Kapper l'a tué."+sTemp+" Il a fait cela pour rendre les Narvals hostiles envers l'amiral et en attirer certains de son côté.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Je vois. Très bien. Parlons d'une autre manière. Vous êtes ici pour une raison, n'est-ce pas ? Que voulez-vous ?";
			link.l1 = "Je ne veux pas de carnage sanglant sur l'Île. Je ne veux pas que des gens meurent. Je n'aime pas l'idée d'éliminer tous les Narvals, bien que je vous assure que les Rivados et nous sommes capables de le faire. Je pense aussi que tout le clan ne doit pas répondre des actions de quelques salauds...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Mais mon vote ne suffira pas - vous devriez officiellement assurer l'amiral que la tentative n'a pas été approuvée par vous et que votre clan ne prévoit pas de tuer Dodson.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Que puis-je faire ? Je suis prêt à m'excuser pour la tentative et pour mes soupçons concernant la mort de Marlow. Je peux lui assurer que les Narvals ne prévoient rien contre lui et je le jurerai sur la sainte Bible. Cela vous suffira-t-il, à vous et à Dodson ?";
			link.l1 = "Je le ferai. Je suis sûr que cela fonctionnera aussi pour Dodson si vous lui rendez visite personnellement. Mais d'abord, je lui parlerai de vos intentions, puis je reviendrai vous voir avec les résultats.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "D'accord. J'attendrai.";
			link.l1 = "Je reviendrai bientôt...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "As-tu déjà parlé à l'amiral ? Des résultats ?";
			link.l1 = "Oui, je l'ai fait. Si vous lui rendez une visite officielle, alors le problème est résolu.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Pour être honnête, je ne m'attendais pas à... C'est une grande nouvelle.";
			link.l1 = "Oui, tu sais, je suis content aussi.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Vous avez rendu un grand service au clan Narval en empêchant un massacre insensé et, peut-être, même l'extermination totale de mon peuple. Je vous offre ce mousquet de tour - vous ne trouverez pas une autre arme comme celle-ci. Vous êtes également autorisé à visiter nos navires sans aucune restriction.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Merci. Un cadeau très précieux. Oui, Donald, encore une chose : fais la paix avec Mary la Rouge. Elle est colérique, mais elle est aussi sincère et honnête. Se disputer avec toi l'a poussée à se séparer du clan et cela lui a presque coûté la vie.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Merci. Un cadeau très précieux. Et je suis vraiment heureux que cela se soit terminé aussi bien.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Dis-lui que je lui demande de me pardonner de l'avoir blessée et pour ces deux raclures qui ont osé l'attaquer. Vous êtes tous deux... amis, n'est-ce pas ?";
			link.l1 = "Tu as raison, Donald. Je vais lui dire. Et je suis vraiment heureux que tout se soit bien terminé.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bonne chance. Viens me voir si tu as des questions.";
			link.l1 = "D'accord. Au revoir !";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! Aussitôt que j'étais perdu dans mes pensées, tu as décidé d'inspecter mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en sortiras pas ainsi !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne fais pas le chevalier médiéval courant l'épée à la main. Range ça, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","Bien sûr.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demanderais de baisser ta lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","Bien sûr.","Comme vous dites...");
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
