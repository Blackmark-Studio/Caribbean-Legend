void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Qu'est-ce que tu veux ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Qu'est-ce que tu veux, "+GetSexPhrase("compagnon","fille")+" ? Si tu m'offres un peu de rhum, je ne vais pas dire non. J'ai tellement tourné en rond dans cette foutue ville que j'ai les jambes prêtes à se nouer toutes seules. Et toi, comment tu t'appelles ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+". Tu ne viens pas de l’‘Aigle’, n’est-ce pas ?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Et moi - "+GetFullName(npchar)+". Et oui, je viens de l’‘Eagle’. Vous aimez notre navire, capitaine ?";
			}
			else
			{
				dialog.text = "Capitaine ? Eh bien, eh bien... Hum... Je suis Antonio Velenta. Et oui, je viens de l’« Aigle ». Notre navire a-t-il attiré votre attention, Capitaine ?";
			}
			link.l1 = "Un navire est un navire. Tu ferais mieux de monter à bord au lieu de traîner en ville—ton capitaine fulmine déjà. Il compte quitter le port avant que la marée ne baisse, et quelque chose me dit, garçon, qu’il ne t’attendra pas.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Bon sang... Je sais, je sais... Mais j'ai encore quelques affaires à régler dans cette ville. Ça te dirait de gagner quelques doublons, hein, Capitaine ?";
			link.l1 = "Les doublons ne sont jamais de refus. Mais les gagner, c'est une chose, s'attirer des ennuis, c'en est une autre. C'est quoi, le boulot ? Parle.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Tu vois, en déchargeant la cale, je suis tombé sur une lettre. Elle n’avait pas l’air d’avoir été cachée exprès, juste posée là parmi de vieux tonneaux. Notre flûte a connu plus d’un abordage, alors impossible de savoir d’où elle vient.";
			link.l1 = "Alors tu as trouvé la lettre, mais qu'est-ce que ça change ?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "C'est adressé à une certaine Marisa Caldera de Porto Bello. Cacheté à la cire... J'ai un pressentiment – ce n'est pas une affaire banale. Peut-être que ça vient d'un capitaine, ou d'un marchand... mais sûrement pas d'un simple marin comme moi ! Sauf que je n'aurai pas le temps de retrouver la destinataire – notre capitaine ne plaisante vraiment pas avec ce genre de choses.  Tu ne voudrais pas me l'acheter ? Je te le laisse pour mille pesos. Toi, tu es capitaine, tu n'auras aucun mal à retrouver cette señorita. Et qui sait, elle pourrait bien te récompenser en or, ou autrement... tu vois ce que je veux dire ?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Eh bien, peut-être que je trouverai ta Marisa.  Quoi qu'il en soit, je n'ai rien à perdre. Sauf mille pesos. Donne-moi la lettre.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Pas assez d'argent (1000)", "Money");
			}
			link.l2 = "Désolé, mais tu devras trouver quelqu'un d'autre. J'ai des choses plus importantes à faire que de livrer des lettres.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Voilà. Prends soin de toi, "+GetSexPhrase("pote","fillette")+", je ferais mieux d'y aller – je ne voudrais pas que mes affaires s'envolent avec l'‘Eagle’.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Qui es-tu ? Que veux-tu ?";
			link.l1 = "Je m'appelle Capitaine "+GetFullName(pchar)+" . Je cherche Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Je ne connais aucune Marisa. Vous vous trompez de porte. Partez maintenant avant que j'appelle les gardes – ils ne mettront pas longtemps à vous jeter dehors.";
			link.l1 = "Père "+sld.name+" m'a dit que vous êtes son ami. J'ai une lettre qui lui est adressée. À en juger par son apparence, elle est très en retard. Je veux la lui remettre en main propre.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, Père... Il est trop bon avec tout le monde, mais il se trompe rarement sur les gens. Tu peux me laisser la lettre. Je veillerai à ce qu'elle lui parvienne.";
			link.l1 = "Pardonnez-moi, señorita, mais je préférerais le remettre en main propre. Elle pourrait avoir des questions sur la façon dont je l'ai obtenu et pourquoi il a mis autant de temps à arriver.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "Et tu t'attends à ce que je croie simplement à tes bonnes intentions ? J'ai vu assez de vauriens au visage vertueux. Laisse la lettre ou passe ton chemin.";
			link.l1 = "Je vous donne ma parole de capitaine que je ne vous ferai aucun mal, ni à vous ni à Marisa. De plus, vous pouvez inviter la garde ou toute autre personne habile avec une arme à notre rencontre. Je n'ai d'autre but que de remettre cette lettre à Marisa en main propre.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "D'accord. Passe demain après onze heures du soir. Je ne peux pas promettre qu'elle acceptera de te voir, mais je lui transmettrai tout ce que tu as dit.";
			link.l1 = "J'y serai. À très vite.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Bonjour, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Tu me cherchais, et me voilà. Dolores a dit que tu avais une lettre pour moi ?";
			link.l1 = "Bonjour, Madame Caldera. Oui, vous voilà. Hélas, il semble que cela ait pris beaucoup de temps pour vous parvenir.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Donné : Lettre pour Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... C'est son écriture... L'écriture de Ramiro !";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Mais comment est-ce possible ? Ça fait deux ans !";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitaine... Comment l'avez-vous obtenu ? Où l'avez-vous trouvé ? Je dois tout savoir ! S'il vous plaît, dites-moi tout ce que vous savez.";
			link.l1 = "Cette lettre m’a été remise par un marin. Il l’a trouvée dans un recoin sombre de la cale de son navire et voulait vous la remettre en main propre, mais il a dû regagner son bâtiment en toute hâte. Il m’a donc demandé de vous retrouver, et me voilà. C’est tout ce que je sais...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Merci, "+GetAddress_Form(NPChar)+"! Merci infiniment ! S'il te plaît, ne pars pas. J'aimerais encore te parler, mais d'abord... il faut que je lise cette lettre.";
			link.l1 = "Bien sûr, Lady Caldera. Je serai là.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Vingt minutes se sont écoulées, Marisa a lu la lettre...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Il a écrit cette lettre avant son dernier voyage. Il voulait me dire qu'il avait l'occasion d'acheter une grande cargaison d'ébène à un marchand de Belize, mais il n'avait pas assez d'argent. C'est alors qu'il a contracté ce prêt... Deux cents doublons... À cause de cela, je ne trouve plus la paix maintenant.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Cela explique tout... Mais, hélas, cela n’allégera pas ton fardeau. Tiens bon, Marisa. L’obscurité n’est pas éternelle, et cette dette ne te hantera pas pour toujours.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Non, Dolores, il n'y en aura pas ! Ramiro a écrit qu'il a une planque... à notre endroit. Si elle est encore intacte, peut-être que je pourrai rembourser la dette et enfin échapper à ce cauchemar.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Le Seigneur t’a accordé sa miséricorde ! Il a exaucé nos prières...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Capitaine, encore une fois, merci de m'avoir apporté cette lettre. Cela compte énormément pour moi... Mais je dois vous demander une faveur de plus. Vous voyez, mon mari Ramiro était tout pour moi, et je n'ai jamais cherché la protection d'un autre homme. Maintenant qu'il n'est plus là, je n'ai plus personne vers qui me tourner, pas de famille à moi\nJe dois rejoindre sa cachette – elle se trouve hors de la ville. Mais j'ai trop peur d'y aller seule, les créanciers de mon défunt mari me poursuivent. Vous avez agi avec honneur en me retrouvant pour remettre la lettre... S'il vous plaît, aidez-moi encore une fois.";
			link.l1 = "Bien sûr, Marisa, je t'accompagnerai. Quand veux-tu partir ?";
			link.l1.go = "Marisa_16";
			link.l2 = "Je suis désolé, señora, mais mon séjour dans votre ville a déjà duré trop longtemps. Les promenades à la campagne ne font pas partie de mes projets.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Je comprends... Vous avez déjà fait plus pour moi que je n'aurais pu l'espérer. Merci, Capitaine, et adieu.";
			link.l1 = "Au revoir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Merci, Capitaine. Venez demain à l'aube, vers sept heures. Je serai prêt.";
			link.l1 = "Alors, jusqu'à notre prochaine rencontre, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, vous voilà... Vous êtes vraiment un homme d’honneur ! Allons-y. Notre chemin passe par la jungle jusqu’à la grotte, non loin de la baie des Mosquitos.";
				}
				else
				{
					dialog.text = "Capitaine, vous voilà... Je savais que vous viendriez. Vous savez, c'est la première fois que je rencontre une femme qui commande son propre navire. Et je vois déjà que vous valez bien n'importe quel homme—tant par votre honneur que par votre noblesse !";
				}
				link.l1 = "Excellent, señora. Alors ne perdons pas de temps. Restez près de moi et ne vous éloignez pas un instant.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Merci, Marisa. Mon père était capitaine et un homme d’honneur – et depuis mon enfance, il m’a transmis ces mêmes valeurs.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Viens à l'aube, vers sept heures. Je serai prêt.";
				link.l1 = "À bientôt, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Vraiment ? A-t-il connu le même sort que mon Ramiro ?";
			link.l1 = "Il aurait sûrement préféré trouver la mort l’épée à la main ou au cœur d’une tempête. Mais le destin en a décidé autrement – il a été terrassé par une maladie dont il n’a jamais parlé à personne.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Je suis désolé pour ta perte, "+pchar.name+" Le Seigneur prend les meilleurs d’entre nous... Et même si nous ne comprenons pas toujours pourquoi, telle est Sa volonté. Tout ce que nous pouvons faire, c’est prier pour le repos de leurs âmes immortelles.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Allons-y. Notre chemin passe par la jungle jusqu'à la grotte, non loin de la baie des Moustiques.";
			link.l1 = "Bien sûr. Reste près de moi et ne t’éloigne pas un instant.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Nous y voilà... Ramiro et moi nous sommes abrités de la pluie ici autrefois, quand nous étions jeunes, avant qu'il ne devienne mon mari. C'est là qu'il m'a dit qu'il gagnerait mon cœur, quoi qu'il en coûte.";
			link.l1 = "Je suis désolé que vous ayez dû venir ici seule, sans votre mari, señora. Des endroits comme celui-ci gardent beaucoup de souvenirs. Regardons autour de nous – peut-être qu’en plus des souvenirs, nous trouverons ce que Ramiro avait gardé pour les moments les plus difficiles.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... Tu as trouvé quelque chose ? Est-ce bien ce que Ramiro a laissé ? Je ne sais même pas ce qui m'effraie le plus – que ce soit vide, ou que ça ne suffise pas à couvrir la dette...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(montre) Voilà, c'est tout ce qu'il y avait dans le coffre. J'espère que ce sera suffisant pour améliorer ton destin.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Je fouille encore dans le coffre.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Capitaine ! Bien sûr ! Cela devrait suffire ! Mais je ne peux pas laisser votre aide sans récompense. Prenez une centaine de doublons. Sans vous, je n’aurais jamais entendu parler de cette cachette et je serais encore en train de me cacher des hommes envoyés par le créancier de Ramiro...";
			link.l1 = "Vous êtes très généreuse, señora, merci. Dans notre métier, l'or n'est jamais perdu.";
			link.l1.go = "Marisa_34";
			link.l2 = "Non, señora. Vous avez bien plus besoin de cet argent que moi. Ce qui compte, c’est que maintenant vous pouvez laisser vos soucis derrière vous et vivre en paix. Ça me suffit largement.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Donné : Amulette 'Cimaruta'", "None");
			notification("Donné : Amulette 'Pêcheur'", "None");
			notification("Donné : Mousquet à mèche", "None");
			notification("Donné : Diamant (10)", "None");
			notification("Donné : Rubis (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Eh bien, "+GetSexPhrase("señor",""+pchar.name+"")+", on ferait mieux d'y aller. Si quelqu'un m'a vu en ville, il se peut qu'on nous suive. Mieux vaut ne pas traîner ici.";
			link.l1 = "Tu as raison, Marisa. Allons-y.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Capitaine, je vous en prie... mon mari gardait cette arme pour protéger notre famille, et je suis certaine — entre vos mains, elle servira une cause juste. Ramiro serait heureux de savoir qu'elle est allée à la personne qui m'a sauvée quand tout espoir était perdu.";
			link.l1 = "D'accord, Marisa, merci. Tu es une femme généreuse et honorable, et je regrette sincèrement que le destin t'ait été si cruel.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Parfois, le Seigneur nous envoie des jours difficiles, voire des années, pour éprouver notre foi, mais Il n'abandonne jamais ceux qui suivent le chemin de la droiture. Il t'a envoyé pour m'aider, et maintenant, j'espère que mon plus grand tourment sera bientôt derrière moi.\nMais pour l'instant, il est temps de rentrer. Nous sommes restés ici assez longtemps, et cela pourrait devenir dangereux, puisqu'ils me cherchent encore.";
			link.l1 = "Bien sûr, señora, allons-y.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha ! Alors voilà notre disparu ! Tu croyais vraiment pouvoir te cacher ici, dans ce trou comme une souris, et que je ne te retrouverais pas ? J’ai retourné toute la ville plus d’une fois, et te voilà enfin."+GetSexPhrase(", et en plus, tu es sortie avec un gamin. Où est mon argent, petite traînée ? Tu as intérêt à me le donner tout de suite, sinon cette grotte sera ta tombe.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Toi...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Alors c'est toi qui gagnes ta vie à extorquer des femmes pour des dettes ? Vu le métier que tu as choisi, l'intelligence n'a jamais été ton point fort. C'est un miracle que tu aies réussi à arriver ici tout seul, au lieu de simplement suivre quelqu'un de plus malin... comme ta propre botte, par exemple.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Ferme-la, héros. Ton tour viendra, mais d'abord je m'occupe d'elle. Elle doit cinq cent vingt-cinq doublons – c'est sa dette, intérêts compris. Soit elle paie tout, soit elle reste ici pour toujours – à nourrir les vers. Mais puisque tu te crois si vertueux, tu peux payer pour elle, et je disparaîtrai.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Tu penses pouvoir entrer ici, insulter une dame, m’ignorer, et repartir d’ici entier, avec les doublons en plus ? On dirait que tu n’es pas très futé. Mais je ne vais pas déclencher une bagarre devant une femme. Voilà ce que je te propose : tu présentes tes excuses à Madame Caldera, tu prends tes doublons, et tu dégages d’ici. Sinon, je vais devoir t’apprendre les bonnes manières, finalement.";
					link.l1.go = "Naemnik_5";
					notification("Vérification réussie (525)", "Dubloon");
				}
				else
				{
					notification("Pas assez d'or (525)", "Dubloon");
				}
			}
			else
			{
				dialog.text = "Ferme-la et attends ton tour. Je m'occuperai de toi plus tard, quand j'en aurai fini avec cette misérable. Elle doit cinq cent vingt-cinq doublons – c'est sa dette, intérêts compris. Puisque tu te crois si vertueux, tu peux payer pour elle, et je m'en irai.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Eh bien, je suis prêt à pardonner tes manières brusques et même ton impolitesse envers moi. Mais si tu veux récupérer tes doublons et quitter cet endroit entier, il va falloir présenter tes excuses à Lady Caldera. Sinon, on verra bien qui manie mieux les armes. Et crois-moi, je ne porte pas la mienne pour faire joli.";
					link.l1.go = "Naemnik_5";
					notification("Vérification réussie (525)", "Dubloon");
				}
				else
				{
					notification("Pas assez d'or (525)", "Dubloon");
				}
			}
			link.l2 = "De toute évidence, tu n’es pas accablé par l’esprit si tu pensais que j’allais attendre mon tour. Et encore moins si tu croyais que je fermerais les yeux sur tous les ennuis que toi et les tiens avez causés à Lady Caldera.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Très bien, fais comme tu veux. Si on peut récupérer l'argent sans prendre de risques inutiles, je ne vois pas pourquoi je me mettrais en danger. Donne-moi les doublons – et file.";
			link.l1 = "D'abord, présente tes excuses à la dame.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Pardonnez-moi, señora. Le diable a pris le dessus sur moi.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Heureux"+GetSexPhrase("","")+"Donne-moi l'or et je m'en vais. J'ai bien assez à faire, pas le temps de bavarder avec toi.";
			link.l1 = "Prends tes doublons et fiche le camp d'ici.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Capitaine, vraiment, je ne comprends pas... Qu'est-ce que cela signifie ?";
			link.l1 = "Cela veut dire que tu ne dois plus rien. Tu es libre.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Mais... je n'ai pas la somme complète pour te rembourser tout de suite. Si tu pouvais attendre un peu...";
			link.l1 = "Tu ne comprends pas, Marisa. Tu ne me dois rien. Tu ne dois plus rien à personne. Et l’argent que tu as trouvé te sera très utile. Retourne à ta vie d’avant – l’église t’attend.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Je... Je n'arrive pas à y croire. Des choses comme ça, ça n'arrive pas, "+GetSexPhrase("caballero","señorita")+" ! Tu as payé une fortune pour moi... comme ça, sans raison ? Et maintenant, tout est fini ? Plus de dettes, plus de poursuites ? Dis-moi, c'est vrai ?";
			link.l1 = "C'est vrai, señora. Tout est fini. Vous ne devez plus rien à personne.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Capitaine, vous êtes si noble ! J'ai l'impression que Dieu vous a envoyé ! Mais je ne sais même pas comment vous remercier. Vous avez... complètement changé ma vie, et moi... que pourrais-je bien faire pour vous ?";
			link.l1 = "Tu n’as rien à faire, Marisa. Vis simplement. Sans peur, sans les chaînes du passé. Retourne à ta vie d’avant et retrouve-y le bonheur – ce sera la meilleure façon de me remercier. Viens, je vais t’accompagner jusqu’en ville.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Qu'avez-vous fait, Capitaine, vous l'avez tué !";
			link.l1 = "C'est vrai, señora. J'ai dû vous protéger, vous et votre honneur...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Oh, Capitaine, ôter la vie à un homme, même à un tel individu, est un péché terrible et lourd ! Il vous faudra prier jour et nuit pour en laver ne serait-ce qu'une infime partie de votre âme immortelle. Dieu m'est témoin, j'aurais pu simplement lui donner tout ce que j'avais et il serait parti... Mais maintenant... maintenant, son sang est sur vos mains, et seuls les cieux décideront si vous serez pardonné !";
			link.l1 = "Peut-être était-ce la volonté du Seigneur. Mais ne nous attardons pas là-dessus. Sortons plutôt de cette grotte.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Capitaine, permettez-moi de vous remercier encore une fois ! Je prierai pour votre santé et votre bien-être, "+pchar.name+". S'il vous plaît, venez à notre église – que le Seigneur vous accorde le pardon de tous vos péchés et Sa bénédiction.";
			link.l1 = "Peut-être que je passerai un de ces jours. Et souviens-toi, Marisa, si je ne vois pas ton joli sourire là-bas, je serai vraiment déçu.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Tu es si bon avec moi. Je serai vraiment heureuse de te revoir dans notre ville. Mais pour l’instant, pardonne-moi, je suis impatiente de remettre de l’ordre dans ma vie et de partager la bonne nouvelle avec Dolores.";
			link.l1 = "Bien sûr, Marisa. Au revoir. Prends soin de toi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Capitaine, permettez-moi encore une fois d’exprimer ma gratitude sans bornes ! Vous avez accompli l’impossible pour moi ! Pour votre bonté et votre noblesse, je tiens à vous raconter comment j’ai réussi à échapper aux mercenaires ces deux dernières années. Peut-être que ce savoir pourra un jour vous être utile aussi.";
			link.l1 = "Merci, señora. Dans ce genre d’affaires, le savoir vaut autant que l’or. Je vous écoute.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "C'est ainsi que j'ai passé ces deux années. Dans un monde où la force compte autant, savoir rester dans l'ombre ouvre des portes dont les autres ne peuvent que rêver.";
			link.l1 = "Merci d’avoir partagé ton histoire, Marisa. Tu as traversé tant d’épreuves, et ton expérience est vraiment précieuse.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Je serai vraiment heureux de vous revoir dans notre ville. Venez donc à notre église—que le Seigneur vous accorde le pardon de tous vos péchés et Sa bénédiction.";
			link.l1 = "Peut-être que je passerai un de ces jours. Et souviens-toi, Marisa, si je ne vois pas ton joli sourire là-bas, je serai vraiment déçu.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Capitaine... Vous êtes si bon avec moi. Mais maintenant, pardonnez-moi, je suis impatient de remettre de l'ordre dans ma vie et de partager la bonne nouvelle avec Dolores.";
			link.l1 = "Bien sûr, Marisa. Au revoir. Prends soin de toi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Vous avez entendu ? Le capitaine "+GetFullName(pchar)+" a payé de sa propre poche les dettes de la veuve Calder ! Peu de gens seraient prêts à se séparer d'une telle somme pour un inconnu. Il existe encore de vrais caballeros en Espagne !", "Ça fait chaud au cœur de voir que l’Espagne abrite non seulement de valeureux caballeros, mais aussi des femmes dont l’honneur et le courage n’ont rien à envier à ceux des hommes.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("On raconte qu’un capitaine a utilisé son propre argent pour libérer la veuve Calder des dettes de son défunt mari ! Peu agiraient avec autant de noblesse. Un véritable homme d’honneur, n’est-ce pas ?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitaine, quel plaisir de vous revoir ! J’espérais que vous passeriez. Peut-être aurez-vous le temps aujourd’hui de rester un peu et de prier ?";
						link.l1 = "Heureux"+GetSexPhrase("","")+" rencontrer, Marisa. Mais j'ai bien peur de ne pas pouvoir m'attarder pour l'instant. Je me souviens de mon devoir envers le Seigneur, mais la prière devra attendre.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Capitaine, vous voilà encore ! Toujours un plaisir. On dirait que le Seigneur ne vous laisse jamais oublier le chemin de l'église... Peut-être trouverez-vous un moment pour prier, après tout ?";
						link.l1 = "Marisa, ça me fait plaisir de te voir. Mais je ne peux pas rester – mes affaires n’attendent pas. Je crois que le Seigneur connaît mes pensées même sans prière.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitaine, quel bonheur de vous revoir ! Chaque jour, je remercie le Seigneur pour votre bonté. Le monde est devenu plus lumineux quand vous m'avez aidé.";
						link.l1 = "Heureux"+GetSexPhrase("","")+"   Heureux de te voir en bonne santé, Marisa. J'espère que la vie ne t'a pas réservé d'autres mauvaises surprises. Tu as l'air bien plus heureuse.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Capitaine, je suis tellement heureuse de vous voir ! Chaque fois que vous venez dans notre église, je me sens en paix. Vous apportez avec vous la lumière des bonnes actions.";
						link.l1 = "Et j'en suis heureux"+GetSexPhrase("","")+" Heureuse de te voir, Marisa. T'es-tu habituée à une vie tranquille, ou t'arrive-t-il encore d'y repenser parfois ?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", si tout le monde remettait sans cesse la prière à plus tard, le monde serait depuis longtemps plongé dans les ténèbres. Mets tes soucis de côté un instant – le repentir te donne la force d’avancer.";
			link.l1 = "Je comprends, Marisa, mais je ne peux vraiment pas en ce moment. Je crois que le Seigneur m'entendra même sans paroles.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", as-tu changé d'avis ? Les péchés ne disparaissent pas d'eux-mêmes, et plus tu attends, plus ils deviennent lourds.";
			link.l1 = "Hélas, je dois m'en aller. Mais la prochaine fois, je promets que je prierai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Mais la foi ne se limite pas à savoir, elle exige d'agir ! Tu ne peux pas repousser indéfiniment le chemin de la rédemption. Ne veux-tu pas ressentir le soulagement de te libérer du poids du péché ?";
			link.l1 = "Peut-être, mais pas maintenant. Que le Seigneur m'entende, même si la prière doit attendre.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Capitaine, ne pensez-vous pas que remettre la repentance à plus tard est déjà un péché en soi ? Un jour, il pourrait être trop tard.";
			link.l1 = "Peut-être, mais j'ai bien peur de ne pas avoir le temps aujourd'hui. La foi m'accompagne, et le Seigneur voit mon repentir même sans prière.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Oui, grâce à vous je peux enfin respirer librement. Que le Seigneur veille sur vous et votre voyage. Peut-être accepteriez-vous de prier avec moi ?";
			link.l1 = "Je crois que tes prières sont déjà assez puissantes. Ce qui compte le plus, c'est que tu sois désormais entouré uniquement de bonté.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", as-tu finalement changé d'avis ? Allons-nous prier notre Créateur ?";
			link.l1 = "Malheureusement, Marisa, je dois y aller maintenant, j'ai des choses à faire.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "J’essaie de ne regarder que devant moi. Maintenant, j’ai un avenir, et c’est grâce à toi. Peut-être devrions-nous remercier le Seigneur ensemble pour cela ?";
			link.l1 = "Je pense que tu t'en sortiras mieux que moi. L'essentiel, c'est que tes prières t'apportent la paix.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", peut-être puis-je vous convaincre de dire au moins une prière ?";
			link.l1 = "Pardonne-moi, Marisa, mais hélas, je n'ai pas le temps en ce moment. Prie aussi pour moi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Capitaine, ce n'est pas ici. La grotte qu'il nous faut est près de la baie des Moustiques.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}