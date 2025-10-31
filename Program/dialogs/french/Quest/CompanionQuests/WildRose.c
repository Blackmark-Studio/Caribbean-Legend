void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Qu'est-ce que vous voulez ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. 'ЛОЩИНА ВЛЮБЛЁННЫХ' ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+", regarde par ici !";
			link.l1 = "Chut, "+npchar.name+", on n'est peut-être pas seuls ici.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Tu me suivais à la trace, ouais, hein ?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "Et il faut croire que j'ai bien fait, ouais, hein ! Qu'est-ce qui s'est passé ici ?";
			link.l1 = "Si je savais, "+npchar.name+", si seulement je savais...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Mon Dieu...";
			link.l1 = "Ouais, la pauvre, on dirait qu'elle a vraiment souffert avant de mourir. Je ne souhaiterais une telle fin à personne...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "Et c'est qui, là-bas, son mari ? Qu'est-ce qu'ils foutent dans la jungle, bon sang ? Ils n'ont donc jamais entendu parler des esclaves en fuite ?";
			link.l1 = "J'ai bien peur qu'ils ne puissent plus répondre à cette question...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Tu crois que celui qui a fait ça est encore dans les parages ?";
			link.l1 = "C'est bien possible. Alors, on ferait mieux de rester discrets, toi et moi – il faut qu'on les repère avant eux.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Trop tard, "+pchar.name+". On dirait qu'on nous a déjà repérés. Regarde là-bas.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Alors, alors, les gars, regardez-moi ça. On dirait bien qu'on est dans un vrai nid d'amoureux, hein, héhé. À peine deux tourtereaux ont-ils rendu l'âme au bon Dieu que deux autres viennent aussitôt prendre leur place...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Très spirituel. Mais tu ne sais sûrement pas compter — contrairement à ces pauvres types, nous ne sommes pas seuls ici.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Eh bien, avec nous, ce sera un peu plus compliqué, tu peux me croire, ouais, hein...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
			case "Naemnik_3":
			dialog.text = "À toutes tes questions — oui. Ça fait plus de deux jours qu'on les pourchasse sur toute l'île avec les troufions. Puis ces salopards se sont divisés. Une partie a fui vers la grotte — la garde les a suivis. Les autres ont filé vers la crique. Dans leur embuscade à un demi-mille à l'ouest d'ici, on a perdu plusieurs gars. Et pendant qu'on se reprenait et se regroupait, ils se sont bien amusés avec cette idiote...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;

		case "Naemnik_4":
			dialog.text = "Touche pas à ton cure-dents, freluquet — t'énerve pas moi et mes gars. J'aurais bien aimé voir comment il t'aurait aidé, c'te machin, si t'avais été entouré par une dizaine des salopards qu'on a butés à la crique. Y en a qu'un qui a eu de la chance — mais ça va pas durer... Une fois qu'il sera entre les mains de Bishop...";
			link.l1 = "Alors, vous êtes ses mercenaires ?";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Sûrement pas des trouffions de garnison. Sans ces lavettes, on aurait chopé ces salopards dès hier — et ce crétin avec sa p'tite femme seraient encore en vie...";
			link.l1 = "Donc, ce n'est pas votre œuvre...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Tu nous prends pour qui, là ? On n'est pas des anges, c'est sûr, mais quand on a envie, on va au bordel, pas...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Il ment, il ment sans arrêt – ce misérable ! Ne l'écoutez pas, "+GetAddress_Form(NPChar)+"! On n'a même pas touché à ces pauvres gens !";
			link.l1 = "Ah bon ? Et pourquoi on devrait vous croire, vous, et pas lui ?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Ouais ? Et si c'était toi qui mentais, en fait ? Tu n'as pas vraiment l'air d'un saint, hein ?";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Eh bien, réfléchissez un peu, pour l'amour de Dieu ! On fuyait cette brute de Bishop, on a couru deux jours dans la jungle, brouillé nos traces – pour quoi ? Pour maintenant faire du mal à une pauvre dame et laisser ces sangsues nous rattraper ? Mes amis ont à peine réussi à traîner leurs jambes jusqu'à cette plage, "+GetAddress_Form(NPChar)+"! Nous n'avions même plus la force de tirer avec nos mousquets, sinon jamais nous n'aurions laissé ces canailles accomplir leur sale besogne... C'est bien eux, on les a vus !..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Eh bien, réfléchissez un peu, pour l'amour de Dieu ! On fuyait cette brute de Bishop, on a couru deux jours dans la jungle, brouillé nos traces – pour quoi ? Pour maintenant s'en prendre à une pauvre dame et laisser ces sangsues nous rattraper ? Mes amis tenaient à peine debout quand ils ont atteint cette plage, "+GetAddress_Form(NPChar)+"! Nous n'avions même plus la force de tirer de nos mousquets, sinon nous n'aurions jamais laissé ces canailles accomplir leur sale besogne... C'est bien eux, on les a vus !..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Ferme-la, Casper, sale chien galeux !";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Qu'est-ce que tu as dit ?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Tu es sourde, ma jolie ? J'ai dit de la fermer. Notre Jerry, il peut raconter des salades pendant des heures – pour ça, il a un sacré talent ! Bishop voulait lui couper la langue et le forcer à la bouffer, mais il a eu pitié – et il n'aurait pas dû, nom d'un chien !";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Mais... Tu l'as appelé Casper, ouais...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Écoute, gamin, explique à ta copine que les gens, même des avortons comme celui-là, ont non seulement un prénom, mais aussi un nom de famille. J'ai souvent entendu dire que les jolies nanas pouvaient être aussi bêtes qu'un sac de paille, mais alors là, que je crève…";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "C'est exactement ce que je vais te faire maintenant, ouais, hein !";
			link.l1 = "Mary, arrête ! Je vais régler ça moi-même. Range ton arme dans son fourreau. Tout de suite.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Oh, on dirait qu'on a affaire à un vrai gentilhomme, ici. Eh bien, ton comportement est vraiment plus digne que les cris de ce mollusque. Il hurlait plus fort que sa pauvre petite femme – à tel point qu'on l'entendait même derrière cette colline. À vrai dire, il nous a même un peu aidés – c'est comme ça qu'on a repéré ces salauds...";
			link.l1 = "Ici, aux Caraïbes, la noblesse est une chose plutôt rare. Maintenant, soufflons un bon coup – il n'y a rien de noble à aller rejoindre nos ancêtres ici et maintenant.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Les seuls vauriens ici, c'est vous. Présente immédiatement tes excuses à Mary, et peut-être qu'on évitera de faire couler le sang.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Difficile de ne pas être d'accord. Mais d'abord, calme ta...";
			link.l1 = "Elle s'appelle Mary Casper. Je pense que ça va éclaircir bien des choses.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper ? C'est sa fille, ou quoi, ha ha ?";
			link.l1 = "J'en doute fort. Mais j'espère que maintenant tu auras assez de bon sens pour reprendre tes paroles.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Retourner en arrière ? Et quoi d'autre ? Tu veux me défier en duel ? Vas-y… À moins que tu n'aies peur de laisser ta précieuse toute seule, au milieu de la jungle, hé-hé. Mes gars et moi, on serait trèèès contents de ce retournement.";
			link.l1 = "Eh bien, voilà votre vrai visage. Vous n'étiez pas si doué pour faire semblant, ouais, hein ?";
			link.l1.go = "Naemnik_bitva";
			break;

		case "Naemnik_22":
			dialog.text = "Vous, monsieur, vous êtes plein de contradictions — si pacifique, et pourtant — un vrai goujat. Cela dit, je suis curieux : vous implorez le pardon de cette rouquine cinglée ?";
			link.l1 = "Elle s'appelle Mary Casper, et si tu ne...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Caspér ? Que je sois damné ! Jerry, ce ne serait pas ta fille, par hasard, hein ? Ha-ha-ha-ha ! J'en crois pas mes oreilles ! Incroyable !";
			link.l1 = "Tu sais ce qui arrive aussi ? Des types comme toi – des idiots qui n'ont entendu parler de l'honneur que par des rumeurs – se comportent avec les dames comme s'ils étaient nés dans une étable. Enfin, à quoi bon s'étonner – quand on a de la sciure à la place du cerveau, on ne risque pas d'avoir de bonnes manières.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Tiens donc... Quel ver insolent. Dis-moi, l'ami, ta nana est douée dans un hamac ? Quoique… j'en doute fort — et je me ferai un plaisir de le vérifier moi-même...";
			link.l1 = "Voilà, vous vous êtes trahi. Vous n'avez pas tenu longtemps. Au combat !";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Vous leur en avez mis plein la vue, "+GetAddress_Form(NPChar)+", - ces salauds-là. Qu'ils brûlent en enfer ! Dommage, je n'ai pas eu le temps de vous aider. Le mousquet que j'avais repéré en venant ici était trop loin. Apparemment, l'un des nôtres l'a perdu en fuyant. J'aurais voulu descendre ce fumier de Primer de mes propres mains.";
			link.l1 = "Apparemment, Primer t'a vraiment embêté, si tu as décidé de revenir.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Et comment qu'il me harcelait. À cause de ce salaud, j'ai le dos tout balafré. Mais le pire, c'est qu'il pouvait nous interdire de boire de l'eau quand ça lui chantait.";
			link.l1 = "Dommage, aucun de ces salauds n'a survécu. On aurait pu en livrer un aux soldats – qui, j'en suis sûr, ne tarderont pas à arriver ici.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Je ne comprends pas trop pourquoi, euh, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Eh bien... Le commandant lui aurait arraché des aveux, lavant ainsi vos noms – le tien et ceux de tes compagnons tombés.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Ouais, bien sûr, ha-ha. Et ensuite William Bishop me dépouillera de ma propre peau — un Noir de la plantation m'en a parlé... Bishop ne plaisante pas avec les fuyards — que tu sois noir ou blanc, ça ne change rien.";
			link.l1 = "J'ai bien peur que tu doives retourner à la plantation, d'une façon ou d'une autre...";
			link.l1.go = "Djerry_5";
			link.l2 = "Donc, tu ne retourneras pas à la plantation de ton plein gré, ouais, hein ?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Eh bien, vous êtes un sacré farceur – on vous l'a déjà dit, ouais, hein ? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Pas de blagues, "+npchar.name+". Tu crois que je suis arrivé ici par hasard ? Je suis allé dans la selva pour retrouver votre groupe, les ramener à la plantation – et puis, gagner un peu d'or. Mais il ne reste plus que toi. On ne tirera pas grand-chose pour ta tête, alors peut-être que je vais te laisser partir. Mais dis-moi – à quoi tu pensais, franchement ? Tu es tout seul. Tous les autres sont morts. Qu'est-ce que tu espères, bon sang ? Te cacher dans les montagnes et les buissons, jusqu'à ce qu'une balle t'attrape, que la fièvre t'emporte ou que tu finisses dans la gueule d'un jaguar ?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Tu es un sacré farceur – on te l'a déjà dit, ouais, hein ? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Pas de blague, "+npchar.name+". Tu crois que je suis arrivé ici par hasard ? Je suis allé dans la selva pour retrouver votre groupe, vous ramener à la plantation — et me faire un peu d'or au passage. Mais au final, il ne reste que toi. Tu ne vas pas me rapporter grand-chose, alors peut-être que je vais te laisser partir. Mais dis-moi — à quoi tu pensais, bon sang ? Tu es seul. Tous les autres sont morts. À quoi tu espères ? Te cacher dans les montagnes et les buissons jusqu'à ce qu'une balle t'atteigne, que la fièvre t'emporte, ou que tu finisses bouffé par des jaguars ?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Mieux vaut comme ça, foi de Dieu, "+GetAddress_Form(NPChar)+" - à mon avis, c'est bien mieux que de crever des tourments que Bishop m'a réservés. Mais en vrai, ce n'est pas si terrible – près du cap Ragged Point, il y a une barque à voile planquée.";
			link.l1 = "Les terres les plus proches de la Barbade, c'est la Dominique avec ses indigènes, et Tobago avec ses Espagnols. Je ne sais même pas ce qui est… pire pour toi.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Je pense que je vais tenter ma chance avec les Dons – des contrebandiers et des pirates jettent souvent l'ancre à Tobago. Oh, je vois, tu désapprouves mon choix, "+GetAddress_Form(NPChar)+". J'ai servi honnêtement mon pays – mais que puis-je faire, puisqu'il m'a envoyé aux carrières ?";
			link.l1 = "Je ne te juge pas, "+npchar.name+"Chacun suit sa propre route. Maintenant, prends autant de poudre et de balles que tu peux – et file. Avant que les soldats ne débarquent ici.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Merci, "+GetAddress_Form(NPChar)+". Et vous, jeune demoiselle, euh, Mary. (s'incline). Nous ne sommes certes pas de la même famille, mais croiser quelqu'un du même nom dans une telle, euh, situation... c'est plutôt inattendu et...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "On peut dire ça, ouais, hein ? Et maintenant, adieu, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", tu as l'air préoccupée ? Tu t'es séparée drôlement vite de ton homonyme, ouais, hein ?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Je voulais juste me débarrasser au plus vite de la compagnie de ce type... Son histoire ne tient pas debout, ouais, hein ?";
			link.l1 = "De quoi tu parles, ma chérie ?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Après ce que j'ai entendu de la bouche de ce sbire de Bishop, je n'ai aucun doute que ces pauvres gens sont morts de sa main. Mais avant ça… Casper, tu as bien écouté ce qu'il disait ?";
			link.l1 = "Et qu'est-ce qui ne t'a pas plu, ma belle ?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Il prétend qu'il y a une barque cachée sur la plage. Mais plus de vingt personnes se sont échappées de la plantation. Donc, la barque doit être assez grande, non ? Jerry est un déserteur de la flotte, il ne peut pas ignorer qu'il aura du mal à manœuvrer un grand bateau tout seul, ouais, hein...";
			link.l1 = "Il n'aura qu'à hisser la voile et prendre le cap – le vent fera le reste. Ouais, hein ? Il prend un sacré risque, mais peut-être que mourir en mer, c'est vraiment mieux que de finir sous la main d'un bourreau de planteur.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Soit. Mais je viens de comprendre qu'il y a encore quelque chose qui ne colle pas... D'après lui, lui et ses amis observaient de loin les exactions des mercenaires sur cette pauvre femme...";
			link.l1 = "Au lieu de filer à toute allure vers ta barque... Ouais, j'ai compris où tu veux en venir, "+npchar.name+". Je devrais peut-être poser encore deux ou trois questions à monsieur Casper... ";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Hé, "+npchar.name+", vieux ! Attends une minute...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Merde !!! Mary, fais attention !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Salaud de vaurien ! On lui a sauvé la vie, et lui ! Qu'est-ce que ça veut dire, "+pchar.name+"? Alors...";
			link.l1 = "Ouais, "+npchar.name+", il ne reste plus personne en vie qui connaissait la vérité sur ce qui s'est passé...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "On ferait mieux de filer d'ici, "+pchar.name+". Si les soldats nous trouvent ici, on va avoir des ennuis, ouais, hein ?";
			link.l1 = "Tu as raison, Mary. Allons-y...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Tu sais, "+pchar.name+", après tout ça, j'aimerais bien boire un bon coup, ouais, hein ?";
			link.l1 = "Je ne vais pas protester, ma chère. J'ai moi-même envie de me rafraîchir le gosier. Allons faire un tour à l'Irlandais Cocu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Excusez-moi de vous avoir réveillé, capitaine...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Tu as frappé, merci pour ça. Maintenant, dis-moi ce que tu veux de moi ?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "T'as bien fait de frapper, l'ami. Si t'étais entré comme ça, tu serais déjà en train de dégringoler les escaliers\nQu'est-ce que tu regardes ? Crache le morceau, pourquoi t'as traîné ta carcasse jusqu'ici ?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Un des habitants souhaite vous voir – Lewis Gernon. Il dit qu'il a une conversation importante à avoir avec vous.";
			link.l1 = "C'est la première fois que j'entends ce nom. J'espère qu'il a vraiment quelque chose d'important, pour me déranger comme ça au beau milieu de… mes affaires. Qu'il entre…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Bonjour, monsieur "+pchar.lastname+". Mademoiselle... Casper.";
			link.l1 = ""+TimeGreeting()+", monsieur "+npchar.lastname+". Je ne me souviens pas que nous nous soyons déjà rencontrés. D'où nous connaissez-vous ?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Vous ne vous souvenez pas ? Ah, je comprends... Mon visage était couvert de sang et de poussière, j'ai moi-même eu peur en me voyant dans le miroir il y a quelques heures...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Tu... tu es bien cet homme, ouais, hein ? On t'a retrouvé et...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "Et ma Susan. Ma pauvre Suzy...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "On pensait que vous étiez mort. Comme… Elle était votre femme, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Oui, madame. C'était ma femme, et j'étais paralysé par la peur... je n'ai rien pu faire. Mon Dieu, mon Dieu...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(en sanglotant) Ils m'ont frappée et m'ont forcée à regarder ça...";
			link.l1 = "Levez-vous, "+GetAddress_Form(NPChar)+"Vous n'y êtes pour rien. Personne n'aurait pu tenir seul face à autant de vauriens.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Ils étaient si nombreux, si nombreux... Mais pourtant, moi...";
			link.l1 = "Mais tout de même, vous avez survécu, et les assassins de votre femme brûlent en enfer. C'est un maigre réconfort, mais c'en est un tout de même, monsieur "+npchar.lastname+". Cependant, je voulais te demander quelque chose...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Ouais, monsieur "+pchar.lastname+"?";
			link.l1 = "Qui c'était ? Les mercenaires de Bishop ou des esclaves en fuite ?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "C'est Jerry Casper et les autres fugitifs qui ont fait ça. Vous vous êtes trompé en accusant Bruce Primer et ses hommes.";
			link.l1 = "Les mercenaires de Bishop ?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Ouais. Bruce, bien sûr, c'était un vrai filou et il faisait beaucoup de sale boulot pour Bishop – mais ce n'était pas un violeur.";
			link.l1 = "Je n'en ai pas vraiment eu l'impression. Mais je ne vais pas vous contredire, "+npchar.name+". Cependant, puisque vous étiez conscient et que vous avez tout vu, vous auriez pu vous lever et...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Pardonne-moi, "+GetAddress_Form(NPChar)+". Vous pouvez me prendre pour un lâche misérable — mais j'étais tellement terrifié que je ne pouvais plus bouger. Quand ces salopards nous ont barré la route à Suzy et moi, j'ai crié de toutes mes forces, je voulais appeler à l'aide.";
			link.l1 = "Et ils vous ont tabassé.";
			link.l1.go = "Lewis_13";
		break;

		case "Lewis_13":
			dialog.text = "Jerry m'a frappé avec la crosse de son mousquet, puis il a dit qu'il allait me découper en morceaux, juste devant Susan. J'ai... j'ai honte de l'admettre, mais je crois que j'ai même perdu connaissance quelques secondes à cause de la peur. Et pendant ce temps, eux...";
			link.l1 = "J'ai compris, monsieur "+npchar.lastname+". Il n'y a rien de honteux dans votre comportement. Peu de gens auraient pu supporter cela. Dommage que vous ne soyez pas intervenu – mais ce qui est fait est fait. Pourtant, je suis heureux que nous ayons tout de même envoyé dans l'autre monde l'un des assassins de votre femme – même s'il a failli réussir à nous duper.";
			link.l1.go = "Lewis_14";
			link.l2 = "Donc, on a failli crever en combattant les mercenaires de Bishop – juste parce que vous aviez la trouille, c'est ça ? Belle excuse, "+npchar.name+". Heureusement qu'on a quand même réussi à comprendre ce qui se passait, même si c'est un peu tard...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Ouais, "+GetAddress_Form(NPChar)+". Je suis venu vous remercier pour cela. Même si, au début, vous l'avez cru...";
			link.l1 = "Bruce Primer a fait pas mal d'efforts pour ça. Il ferait mieux de faire attention à ce qu'il dit...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Ouais, "+GetAddress_Form(NPChar)+". Je suis venu vous remercier pour cela. Même si au début vous l'avez cru...";
			link.l1 = "Bruce Primer y a mis pas mal d'efforts pour ça. Il ferait mieux de faire attention à ce qu'il dit...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Hélas, nous avons tous commis des erreurs ce jour-là... Susan et moi n'aurions pas dû aller nous promener à Ragged Point, Bruce aurait mieux fait de se taire à temps... Et vous, vous n'auriez pas dû faire confiance à Jeremy. Mais grâce à Mademoiselle Casper, la justice a été rétablie.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Je me doute de ce que vous voulez me demander, monsieur "+sld.lastname+". Mais je n'ai rien à voir avec cette personne.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Je sais, mademoiselle. Je l'ai compris dès que je suis entré dans cette pièce. Il n'y a pas la moindre ressemblance entre vous et lui. Et pourtant, Susan... elle était convaincue que rien n'arrive par hasard dans ce monde.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Votre femme avait raison. Je m'en suis rendu compte plus d'une fois, ouais, hein ? Et "+pchar.name+" moi aussi.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "C'est vrai. Cependant, je ne pense pas que ce soit le moment pour des discussions philosophiques. Ça ne vous aidera sans doute pas, "+npchar.name+". Seul le temps pourra aider à surmonter ça.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Vous avez sans doute raison, monsieur "+pchar.lastname+". Eh bien, merci encore à vous et adieu. Je prierai pour vous et pour Mlle Casper.";
			link.l1 = "Prends soin de toi, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Je sais, ma belle, j'ai failli laisser filer ce salaud...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Le salaud qui s'appelle Jerry Casper.";
			link.l1 = "C'est ça... Attends... tu crois vraiment qu'il...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Je sais que c'est vraiment idiot...";
			link.l1 = "Bien sûr ! Et si tu t'étais appelée Smith ou Jones ? Y'en a des tonnes qui traînent dans les rues — et y'en a forcément un qui fait des saloperies... Et ce Jerry, qu'il brûle en enfer — peut-être qu'il n'est même pas un vrai Casper...";
			link.l1.go = "Mary_34";
			link.l2 = "C'est bien ça, ma chère. Ce foutu Jerry aurait très bien pu donner un faux nom de famille – voilà tout.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "Et pourtant... Je sais que tu ne me comprends pas, mais imagine juste ce que tu penserais si c'était ton nom de famille qu'il portait "+pchar.lastname+".";
			link.l1 = "Ce n'est pas la même chose, Mary. "+pchar.lastname+" - un nom de famille noble, hein...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "Et pourtant... Je sais que tu ne me comprends pas, mais imagine juste ce que tu penserais si c'était ton nom de famille à lui "+pchar.lastname+".";
			link.l1 = "Ce n'est pas la même chose, Mary. "+pchar.lastname+" - un nom de famille noble, hein...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "Et les Casper, c'est quoi, des gens sans nom, sans famille, ouais, hein ? Je devrais sans doute remercier le Seigneur chaque jour que tu m'aies remarquée, moi, et pas quelque pimbêche prétentieuse…";
			link.l1 = ""+npchar.name+", je ne voulais pas du tout dire ça – tu comprends bien. Les membres d'une famille noble sont liés par le sang – et ce n'est pas du tout la même chose que de simplement porter le même nom de famille que quelqu'un. D'ailleurs, comme je l'ai déjà dit, ce quelqu'un a très bien pu se l'approprier…";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Ce n'est pas seulement ça, "+pchar.name+"...";
			link.l1 = "Chérie, on a eu une longue et dure journée. On a marché des kilomètres dans la jungle, on aurait pu y rester… et après ça, on n'a même pas pu dormir correctement. Rien d'étonnant à ce que des idées bizarres te passent par la tête. On a juste besoin de bien dormir, tous les deux.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Je ne trouve pas ça bizarre du tout, mais bon... on en reparle demain.";
			link.l1 = "Une fois reposés, on comprendra tout plus vite. Allonge-toi, ma chérie, il faut qu'on laisse cette journée derrière nous.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "Tout va bien avec vous, "+GetAddress_Form(NPChar)+"Vous avez l'air bizarre, comme si vous aviez vu un fantôme. Peut-être que vous prendriez un peu de rhum ? Ou du vin ? On a un excellent choix, ça ne vous ferait pas de mal de vous détendre.";
			link.l1 = "Au diable la boisson. Je cherche une fille...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Alors là, vous vous trompez d'endroit, capitaine. Ici, c'est une taverne, pas un bordel. Sortez donc, et juste en face, vous verrez...";
			link.l1 = "Écoute, je n'ai pas envie de plaisanter. Je cherche une fille rousse, en casaque rouge, elle est armée. Elle s'appelle Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Puisqu'on ne plaisante plus, alors je n'ai rien à vous dire. Mon service a commencé il y a une heure, et je n'ai vu ici aucun rouquin en casaque rouge.";
			link.l1 = "Alors, elle est partie dans la nuit... Mais où aurait-elle bien pu aller ?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Bonjour, mon amour ! Tu as dormi si longtemps...";
			link.l2 = "Tu m'as vraiment fait me faire du souci, ouais, hein ? "+npchar.name+". Ne disparais plus comme ça, sans prévenir...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Je ne voulais pas te réveiller. Et puis, toi aussi, parfois tu disparais comme ça, sans rien dire...";
			link.l1 = "Et tu as décidé de me rendre la pareille ?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "En fait, j'avais juste besoin de rester seule avec mes pensées, ouais, hein ? Je ne voulais pas que tu t'inquiètes.";
			link.l1 = "Quelque chose te tracasse ?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Notre conversation d'hier. Sur les noms de famille, les liens du sang...";
			link.l1 = "Alors, tu m'en veux quand même...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Pas du tout, mon cher, ce n'est pas ça. C'est juste que j'ai soudain réalisé que je ne sais absolument rien sur ma famille. Toi, tu es le fils d'une famille noble. Les gars du navire, de temps en temps, racontent des choses sur leurs proches. Et moi, je n'ai rien à raconter – je n'ai jamais connu mes parents. Merde, je ne sais même pas où je suis née…";
			link.l1 = "N'est-ce pas sur l'Île de la Justice ?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Éric, l'homme qui m'a élevée, l'affirmait aussi. Mais si c'est vrai, pourquoi aucun habitant de l'Île n'a jamais parlé de mes parents, même pas évoqué leur existence ? Un jour, j'ai posé la question à Donald Greenspy, mais il n'a rien su me répondre clairement.";
			link.l1 = "Ou alors tu n'as pas voulu parler.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Voilà ! Et j'ai pensé exactement la même chose, ouais, hein ? Tu sais, avant, je vivais ma vie sans trop me poser de questions. Mais hier, quand on est tombés sur ce salaud de Jerry... je me suis demandé – qui était mon père ? Ma mère ? Pourquoi on ne m'a jamais parlé d'eux, comme s'ils n'avaient jamais existé ? Et si mon père était un vaurien, tout comme ce Jerry ?";
			link.l1 = "Ça n'a aucune importance, "+npchar.name+". Tu as été élevé par d'autres personnes – et elles l'ont fait avec honneur.";
			link.l1.go = "Mary_50";
			link.l1 = "Je doute que ce soit le cas. Et j'ai du mal à voir en quoi ça change quoi que ce soit, vu que tu n'y avais jamais vraiment pensé avant, ouais, hein ?";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Mais pour moi, c'est important, "+pchar.name+", ouais. Je veux, j'ai le droit de savoir qui étaient mes parents. Tu n'es pas d'accord avec ça, hein ?";
			link.l1 = "Bien sûr, je suis d'accord, il ne peut pas en être autrement. Mais si on veut vraiment apprendre quelque chose sur ton père et ta mère, c'est seulement sur l'Île de la Justice. Après tout, tu ne connais même pas leurs noms, hein ?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Mais pour moi, c'est important, "+pchar.name+", ouais. Je veux, j'ai le droit de savoir qui étaient mes parents. Tu n'es pas d'accord avec ça, hein ?";
			link.l1 = "Bien sûr, je suis d'accord, il ne peut pas en être autrement. Mais si on veut vraiment apprendre quelque chose sur ton père et ta mère, ce sera seulement sur l'Île de la Justice. Après tout, tu ne connais même pas leurs noms, ouais, hein ?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "C'est bien ça, mon chou. On n'en a jamais parlé devant moi, ouais, hein ?";
			link.l1 = "Donc, il est trop tôt pour aller fouiller dans les archives des colonies anglaises. D'abord, il faudra retourner à ce cimetière de navires et essayer d'y trouver des traces de ta lignée.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Je suis contente que tu me comprennes, "+pchar.name+". Merci à toi.";
			link.l1 = ""+npchar.name+", tu m'étonnes, vraiment. C'est le moins que je puisse faire pour toi, ma chérie.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "J'ai quand même vécu presque vingt ans sans rien savoir sur eux...";
			// dialog.text = "Au bout du compte, pendant plus de vingt ans, ça ne m'a absolument pas préoccupée...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Alors je peux encore tenir un peu, ouais, hein ?";
			link.l1 = "Je vois que c'est important pour toi, et que tu en as besoin, "+npchar.name+". Alors je vais essayer de ne pas te faire attendre. Maintenant, allons-y, il faut retourner au navire. Là-bas, je me sens plus tranquille pour toi, en tout cas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. 'ДИТЯ ОСТРОВА' ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Les rivages de chez moi... Tu sais, "+pchar.name+", tu sais, j'ai l'impression que si on revenait ici dans dix ans, tout serait exactement pareil qu'aujourd'hui, ouais, hein ?";
			link.l1 = "Peut-être, "+npchar.name+", peut-être. Les navires de l'anneau intérieur resteront à flot, mais les gens ici seront déjà d'autres, ouais, hein ?";
			link.l1.go = "Mary_62";
			link.l2 = "J'en doute fort – ici, tout ne tient plus que par la parole donnée. Et par le génie du Mécano.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "Et tu sais, je ne me souviens même plus vraiment de ceux qui vivaient sur ces épaves il y a dix ou quinze ans. Juste des personnes qui m'étaient les plus proches – Alan, Eric...";
			link.l1 = "Sans doute, c'est comme ça que ça doit être. On ne peut pas se souvenir de tout et de tout le monde. Moi aussi, j'oublie des noms et des visages — de l'époque de Paris, sans parler de la Gascogne. Et je croyais que ça n'arrivait qu'aux vieux, ouais, hein ?";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "Tu sais, je ne me souviens même plus vraiment de ceux qui vivaient sur ces épaves il y a dix ou quinze ans. Juste des plus proches, comme Alan, Erik...";
			link.l1 = "Sans doute, c'est comme ça que ça doit être. On ne peut pas se souvenir de tout et de tout le monde. Moi aussi, j'oublie des noms et des visages — de l'époque de Paris, sans parler de la Gascogne. Et je croyais que ça n'arrivait qu'aux vieux, tu vois.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Mais cet endroit... C'est comme un autre monde, ouais, hein ? Tu te rends compte, certains de ceux qui sont arrivés ici il n'y a pas si longtemps affirment que le temps passe ici presque trois fois plus vite que sur la Grande Terre...";
			link.l1 = "Ha ha, quel âge tu as alors ?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Je parlais sérieusement, ouais, hein ? "+pchar.name+", ouais, hein !";
			link.l1 = "Bon, soyons sérieux, il est temps de passer aux choses sérieuses. Y a-t-il parmi les narvals quelqu'un de plus âgé que Greenspy ?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmmh, non, il me semble que non. Mais je t'ai déjà dit qu'il ne m'a rien répondu quand je lui ai posé la question.";
			link.l1 = "Et pourtant, je n'ai pas d'autres idées sur qui pourrait nous aider à comprendre ce qui s'est passé il y a vingt ans. Du moins, pas pour l'instant. Alors, cap sur l’‘Esmeralda’.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" et Mary, quelle rencontre ! Je suis content de vous voir ici... en vie, hé hé. Ce dernier mois, deux ou trois navires se sont échoués près de l'anneau extérieur – la mer est sacrément agitée en ce moment. Ouais, et ne forcez pas la porte fermée – vous pourriez casser la serrure, et c'est moi qui devrai la réparer après. Vous allez voir Donald, non ?";
			link.l1 = "Et bonne journée à toi aussi, l'ami. C'est à lui-même. Mais, vu que la porte est fermée à clé, soit il est passé sur un autre navire, soit il ne veut pas voir de vieux amis.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Ni l'un, ni l'autre, ha ha. Greenspy est sur l'anneau extérieur en ce moment, à l'entraînement.";
			link.l1 = "Des exercices ? Vraiment ? Il se prépare à une nouvelle guerre contre les Rivadans, ouais, hein ?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "En fait, elle n'a jamais vraiment cessé, "+pchar.name+". Ces derniers temps, il y a eu beaucoup moins d'accrochages qu'avant. Mais bon, à la taverne de Sancho, il y a toujours quelqu'un pour en coller une à un autre... et parfois, ça finit même au couteau.";
			link.l1 = "Hmm, il me semble qu'avant, les membres des clans ne traînaient pas dans la taverne.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Eh bien, certaines choses ont changé depuis votre départ de l'Île. Donald et Eddie arrivent à tenir les gens en main. Pour l'instant. Mais qui sait ce qui arrivera demain ? C'est le vieux Donnie qui a lancé tout ça…";
			link.l1 = "J'ai eu tant de mal à empêcher un massacre sur l'Île, et c'est pour que vous jouiez encore aux petits soldats ici ? Et ça fait longtemps qu'il traîne sur l'anneau extérieur ?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Les exercices, c'est bien, mais est-ce que ça ne risque pas de fragiliser encore plus la trêve déjà bancale ? Et ça fait combien de temps que Grinspie fait marcher les gars au pas ?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Ça fait trois jours. Il doit revenir demain avant midi. Avec l'ardeur qu'ils mettent à rincer leurs mousquets là-bas, d'ici demain, ils n'auront plus rien pour tirer ! Ha-ha !";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Schmidt_6":
			dialog.text = "Ça fait trois jours. Il doit revenir demain avant midi. Avec l'ardeur qu'ils mettent à rincer leurs mousquets là-bas, d'ici demain, ils n'auront plus rien pour tirer ! Ha-ha !";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "Ma cabine sur le 'Ceres Smithy' est-elle toujours libre ? Ou bien quelqu'un a déjà eu le temps de s'y installer ?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Tout est exactement comme le jour où tu y es allée pour la dernière fois. On n'a même pas ouvert la porte. À vrai dire, la serrure non plus n'a pas été nettoyée ni huilée pendant tout ce temps. Alors, si jamais faut la forcer — dites-le simplement.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;

		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Bien sûr. Merci, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "Tout est vraiment resté comme avant. Toutes les choses sont à leur place – comme si je n'étais jamais partie d'ici… C'est ici qu'on s'est rencontrés pour la première fois, "+pchar.name+". Tu te souviens ?";
			link.l1 = "Bien sûr ! Tu leur as tellement mis la raclée que je me suis dit – faudrait pas que je me retrouve à leur place !";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Tout ne s'est pas du tout passé comme ça, ouais, hein ! Tu m'as littéralement arrachée des griffes de la mort !";
			link.l1 = "On dirait que cette rencontre m'était destinée par le destin lui-même.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Tu le penses vraiment, mon chéri ?";
			link.l1 = "Bien sûr, ma chérie. Et depuis ce jour, je la remercie chaque jour de m'avoir mené tout droit sur le 'Cérès Smithy’.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Dis-moi, à quoi tu as pensé en me voyant pour la première fois ?";
			link.l1 = "Eh bien... Je me souviens seulement que, quand c'est arrivé, mon cœur voulait presque s'arracher de ma poitrine. Tu étais tellement...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Laquelle ?";
			link.l1 = "Aucune femme ne t'arrive à la cheville. Ta grâce, ta voix… et ce pourpoint rouge. Je n'ai pas eu la moindre chance de te résister. J'avoue, je me suis toujours demandé : pourquoi lui ? Pourquoi un pourpoint rouge, et pas une robe, une chemise ou un corset ?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Je l'ai trouvé quand j'avais neuf ans, sur l'anneau extérieur. À l'époque, j'adorais m'y promener — explorer des choses nouvelles, trouver des objets qu'on ne voyait pas sur l'île, surtout des livres. J'ai eu terriblement envie de l'essayer, mais à ce moment-là, j'aurais juste pu me noyer dedans. Je l'ai caché là où je mettais toutes mes trouvailles — dans un des nids-de-pie qui sortaient de l'eau.";
			link.l1 = "Et quand il t'a convenu, tu t'es souvenue de lui ?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Il y a quelques années, en traînant dans le ring, je suis tombée sur un livre parlant d'un brave capitaine en habit rouge. Il n'avait peur de rien, il combattait des centaines d'ennemis pour l'amour de sa vie et ne connaissait pas la peur. C'est là que je l'ai essayé pour la première fois. Ça me donne confiance en moi...";
			link.l1 = "Et un charme unique, ma chère ! Mais tu sais quoi ? Là, tout de suite, je n'ai envie que d'une chose... l'enlever de toi...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "Alors, qu'est-ce que tu attends, mon vaillant capitaine ?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Bonjour, mon cher. Les narvals viennent juste de revenir sur l’'Esmeralda' et la 'San Gabriel', et Donald est avec eux. Je l'ai vu dans l'une des chaloupes, ouais, hein ?";
			link.l1 = "Bonjour, bonjour... Pour être honnête, après une nuit pareille, j'aurais dormi jusqu'à midi, et toi tu es déjà debout, toute légère.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Hier, on a parlé de la casaque et du nid-de-pie où je l'avais cachée autrefois... Et soudain, une telle nostalgie m'a envahie — pour ces moments où je m'y réfugiais loin de tous, juste pour lire en silence des livres sur le vaste monde... J'ai pas pu résister, et j'y suis allée à la nage. Avant, je pouvais y rester des heures, mais aujourd'hui... je m'y suis juste assise pour voir le lever du soleil. Et j'ai compris : plus que tout au monde, je veux être près de toi.";
			link.l1 = "Et moi, je suis avec toi, "+npchar.name+". Alors, on va voir Donald ? On aura des choses à lui dire.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, je suis ravi de vous voir ! On m'a déjà parlé de votre visite d'hier. Je comptais passer moi-même vous voir au 'Cérès Smithy’, mais vous avez devancé le vieux. Ah, si seulement j'avais encore votre âge...";
			link.l1 = "Eh bien, toi, t'en as de l'énergie à revendre, comme on l'a compris. Comment se sont passés les exercices ?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Mieux que ce que j'attendais. On a répété l'embarquement sur les navires ennemis, l'assaut des cabines… Bref, on a bossé comme il faut. J'ai peut-être un peu trop poussé les gars, mais ça ne leur a fait que du bien. Ça faisait longtemps qu'ils ne s'étaient pas dégourdi les jambes, oh, ça faisait longtemps, ha ha.";
			link.l1 = "Et alors, si je peux me permettre, qu'est-ce qui t'a poussé à de tels exploits ? Tu t'ennuyais sur l'Île, ouais, hein ?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hmm, j'entends comme une pointe de mécontentement dans ta voix, "+pchar.name+". Je peux, bien sûr, comprendre ses raisons...";
			link.l1 = "Vraiment, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Tu as dû pas mal courir sur ces carcasses de navires pour éviter qu'on s'égorge tous ici – je ne l'ai pas oublié. Personne ne l'a oublié.";
			link.l1 = "Et voilà comment tu as récompensé tous mes efforts ! On dit vrai, hein ? Le monde ne fait qu'accabler un vrai guerrier.";
			link.l1.go = "Grinspy_5";
			link.l2 = "Et je dois dire que je comptais bien plus sur ton bon sens que sur celui des pirates ou des Rivares.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Laisse-moi finir. Ouais, on a réussi à préserver la paix – mais nos différends n'ont pas disparu pour autant. Surtout avec ces païens à la peau sombre. La semaine dernière, un des Narvals a été tué lors d'une bagarre à la taverne. Mais on ne s'est pas laissés faire non plus...";
			link.l1 = "Ouais, ouais, c'est exactement comme ça que tout commence, hein ?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Laisse-moi finir. Ouais, on a réussi à préserver la paix – mais nos différends n'ont pas disparu pour autant. Surtout avec ces païens à la peau sombre. La semaine dernière, un des Narvals a été tué lors d'une bagarre à la taverne. Mais on ne s'est pas laissé faire non plus...";
			link.l1 = "Ouais, ouais, c'est toujours comme ça que tout commence, hein ?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Tu te trompes sur deux choses, "+pchar.name+". D'abord, ça ne commence pas, ça continue. Si tu croyais naïvement que tu avais mis fin à tout ça, eh bien, tu te trompes. Et puis, je ne suis pas une sainte pour tendre l'autre joue. Les Noirs recommencent à faire des vagues, et ça ne me plaît pas. À Dexter non plus, d'ailleurs, mais il s'imagine être un grand politicien et préfère rester au-dessus de la mêlée. Alors, après réflexion, j'ai choisi, à mon avis, la façon la plus... indolore de préserver une paix fragile.";
			link.l1 = "Tu as décidé de faire peur aux Rivadans avec tes sermons ?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Il y a quelques semaines, un galion anglais chargé de matériel militaire s'est échoué sur l'anneau extérieur — il y avait de tout à bord... Mais surtout, une cinquantaine de fusils tout neufs et de la bonne poudre. Et aussi des chaloupes... La peinture n'avait même pas eu le temps de sécher ! Les vieilles étaient toutes pourries, et après les tempêtes, il reste pas grand-chose en bon état, je te le dis...";
			link.l1 = "Et tout ça est devenu la propriété des narvals ?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Peut-être que j'en aurais parlé à l'Amiral, mais puisqu'il se croit plus malin que tout le monde, moi non plus, j'ai pas envie de passer pour un idiot. Mon plan, d'ailleurs, il a marché, tu vois.";
			link.l1 = "Black Eddie t'a envoyé une lettre où il promet de ne plus planter tes gars sur des couteaux ?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Black Eddie a ordonné à ses Noirs de se tenir à carreau. Je craignais qu'en mon absence, ils se montrent plus provocants — mais c'est tout le contraire qui s'est produit : les Rivares restent tranquilles et gardent leurs distances, aussi bien avec mes gars qu'avec les civils, qu'ils emmerdaient de temps en temps. Un Noir reste un Noir — ils ne comprennent que la force. C'est ce que disait Alan, et que ce rafiot coule sur-le-champ s'il avait tort !";
			link.l1 = "Et si, au bout d'un moment, ils recommencent à faire les malins, tu vas faire pleuvoir du plomb sur la 'Furie' et le 'Protecteur' avec tes nouveaux mousquets, juste pour leur donner une bonne leçon ?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "L'idée est audacieuse et effrontée, mais je pense qu'on n'en arrivera pas là. Peut-être qu'on fera juste semblant de préparer un raid contre leurs navires – et ensuite Leighton prendra son courage à deux mains et finira par intervenir. Il a beau avoir pris la grosse tête, c'est quand même un homme prévoyant. La destruction ni de notre clan, ni des Noirs n'est dans son intérêt – trois centres de pouvoir à peu près égaux assurent au moins un certain équilibre. Il suffirait que l'un d'eux tombe – et tout partirait en vrille. Je suis sûre qu'il le comprend – mais pour une raison ou une autre, c'est à moi de faire son boulot à sa place.";
			link.l1 = "Je passerai peut-être le voir pendant qu'on sera ici – à moins qu'il ne commence ses sermons en retour, ha-ha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "J'essaierai de passer le voir à l'occasion – pour lui en parler. Qui sait, il m'écoutera peut-être, ouais, hein ?";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "S'il y a bien quelqu'un qui pourra le convaincre de tenir les Noirs en respect, c'est toi, "+pchar.name+". Cependant, à voir vos têtes, je comprends bien que vous n'êtes pas venus pour bavarder politique. Dites-moi ce qui vous amène.";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Mes parents, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Je ne comprends pas très bien ce que tu veux de moi, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Parle-moi d'eux, je t'en prie, ouais, hein ? Tu les as connus ! Je t'ai déjà posé des questions à leur sujet, mais tu n'as pas voulu me répondre...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "Et donc tu as décidé d'amener Charles ici, ha-ha-ha ! T'es incroyable, ma fille, que le tonnerre me frappe ! Si je n'ai pas parlé avec toi de ton père et de ta mère, c'est juste parce que je ne les ai jamais connus, voilà tout !";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Mais tu es le membre le plus âgé de notre clan, ouais, hein ! Tu es ici depuis aussi longtemps que je me souvienne...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Je suis arrivé sur l'Île il y a un peu moins de vingt ans, déjà après ta naissance. Tu étais encore une toute petite, tu courais et tu rampais sous les tables et les tabourets, ne laissant aucun répit à Éric Udette… Bien sûr, je lui ai demandé d'où venait cette petite tornade, et il m'a répondu que tu étais née sur l'Île quelques années plus tôt. Il n'a rien dit à propos de ton père ou de ta mère. Et s'il l'a fait – soit je ne m'en souviens pas, soit je l'ai oublié…";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " Tant d'années ont passé... Je comprends, Donald, ouais, hein ? ";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Dommage qu'Eric ne soit pas avec nous — il était déjà dans cet endroit bien avant moi. D'ailleurs, quand il parlait de tes nouvelles frasques, il mentionnait souvent Aurélie Bertin. Cette vieille dame t'adorait, ça je m'en souviens bien... Je ne m'étais jamais posé la question, mais je pense qu'elle était déjà sur l'Île quand tu es née. Peut-être qu'elle pourra t'aider ?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Peut-être bien. Ça me fera une bonne raison d'aller la voir – je ne me rappelle même plus la dernière fois que je lui ai rendu visite. C'est pas très joli, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Je ne pense pas qu'elle t'en veuille. Mais ne la bousculez pas trop – j'ai entendu dire qu'elle était souffrante. On ne sait jamais, hein…";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Tais-toi, Donald, tu vas nous porter malheur ! Aurélie nous enterrera tous, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Viens, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Salut, "+npchar.name+". On se revoit bientôt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Seigneur miséricordieux, j'ai cru que mon cœur allait sortir de ma poitrine. On ne peut pas effrayer les gens comme ça, ouais, hein ?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian ! Je ne m'attendais pas à te voir ici, ouais, hein ? Qu'est-ce que tu fais là ? Et où est Aurélie ?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "Salut à toi aussi, Mary. Et à vous, "+pchar.name+". Aurélie est malade, tu ne le savais pas ? Je veille sur elle à la demande de frère Julian. Il me donne des potions que je lui fais boire, mais… on dirait que ça ne marche pas vraiment. En ce moment, elle est dans la cabine, à la poupe, elle dort. Je l'y ai emmenée pour pouvoir ranger ici.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "On l'a appris seulement aujourd'hui, ouais, hein. Donald nous l'a dit. Comment elle va ?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Mal. Elle se plaint de faiblesse dans tout le corps, elle ne quitte presque plus son lit. Parfois, elle marmonne des choses incompréhensibles, des bêtises... J'ai déjà entendu tant d'histoires sur des temps révolus que j'en ai perdu le compte.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hmm, c'est justement pour une histoire comme celle-là qu'on est venus. J'espère qu'elle acceptera de nous parler...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Est-ce vraiment nécessaire, Mary ? Je ne pense pas qu'il faille la déranger dans cet état.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Ça concerne mes parents. Aurélie a peut-être pu les connaître. C'est très important pour moi, Gillian, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Il n'y a pas de remède sur l'île qui pourrait améliorer son état ?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Frère Julian lui prépare des tisanes. Mais elles ne font effet que pour un temps. Et encore, elle refuse de les boire, alors je dois presque les lui faire avaler de force. Parfois, j'ai peur qu'elle s'étouffe tout simplement avec — il faut encore la forcer à tout avaler...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Pauvre Aurélie ! Personne sur l'Île ne peut vraiment l'aider, ou quoi ?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Tu sais bien qu'il n'y a pas de vrai médecin ici. Et puis, qu'est-ce que tu pourrais faire, hein ? La vieillesse, tu sais, ça n'épargne personne...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", peut-être qu'on pourrait amener quelqu'un de notre navire ?";
			link.l1 = "J'ai peur, "+npchar.name+", ici il ne faut pas un chirurgien de bord, mais un vrai médecin expérimenté.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Je suis prête à croire même à la magie, si ça peut aider, ouais, hein ?";
			link.l1 = "Hmm... De la magie ? Peut-être qu'il faudrait demander à Chimiset...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimisetu ? Le sorcier des Noirs ? "+pchar.name+", vous êtes sérieux ?";
			link.l1 = "Comme jamais. Qu'il soit noir ou blanc, c'est bien la dernière chose qui m'importe en ce moment. Je ne sais pas qui d'autre pourrait aider Aurélie. Je pense que vous non plus. Alors, laissez-moi passer et surtout, ne songez même pas à m'en empêcher.";
			link.l1.go = "Jillian_16";
			link.l2 = "Plus que jamais. Aucun remède ni les prières du frère Julien n'aident Aurélie. Chimiset, c'est notre dernier espoir.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Je n'en crois pas mes oreilles ! Mais c'est… un impie !";
			link.l1 = "Et ça, c'est une femme mourante, à deux doigts d'oublier jusqu'à son propre nom. Ouais, c'est un sorcier, mais j'ai entendu dire qu'ils sont capables de beaucoup, vraiment beaucoup. Et s'il arrive à lui rendre la raison — est-ce que ça compte vraiment, sa foi, maintenant ?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Je n'en crois pas mes oreilles ! Mais c'est… un impie !";
			link.l1 = "Et ça, c'est une femme mourante, à deux doigts d'oublier jusqu'à son propre nom. Oui, c'est un sorcier, mais j'ai entendu dire qu'ils sont capables de beaucoup, vraiment beaucoup. Et s'il peut lui rendre la raison — est-ce que sa foi a encore la moindre importance ?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", écoutez, moi aussi j'aime beaucoup Aurélie... Dieu m'est témoin – je fais tout ce qui est en mon pouvoir pour soulager ses souffrances ! Mais vous comptez vraiment laisser cet hérétique noir faire son rituel dans cette cabine ? Et s'il brûle le navire pendant son cérémonial, ou s'il décide de sacrifier quelqu'un ?";
			link.l1 = "On ne laissera pas faire ça, "+npchar.name+", je vous assure.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "Et moi, je vous assure à tous les deux que si jamais quelqu'un apprend ça… Vous imaginez seulement ce qui va se passer ici ? Les autres habitants n'aimeront pas ça, et alors les narvals — encore moins !";
			link.l1 = "Vous avez raison. Ce n'est pas Chimisetu qu'il faut amener ici, mais Aurélie qu'il faut conduire à lui.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Vous ne l'avez pas vue – la vieille tient à peine debout. Ce sera un miracle si elle ne passe pas par-dessus bord !";
			link.l1 = "Eh bien, parfois il ne nous reste plus qu'à espérer un miracle. Ouais, et, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Quoi d'autre ?";
			link.l1 = "J'espère que vous saurez garder cela pour vous. Vous êtes une fille intelligente, et vous avez bien compris la situation... Les troubles sur l'Île pourraient facilement dégénérer en bain de sang, et personne ne veut ça, hein ?";
			link.l1.go = "Jillian_22";
			link.l2 = "Pas un mot à personne, c'est clair ? On vous a fait confiance – ne nous forcez pas à le regretter. Je pense que vous comprenez que si notre projet cesse d'être un secret, il y aura un massacre sur l'Île comme on n'en a jamais vu.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "D'accord. Mais alors faites en sorte que personne ne vous voie l'emmener sur le 'Protector’... Sinon, je vais devoir répondre à des questions gênantes.";
			link.l1 = "Nous vous éviterons d'avoir à donner des réponses embarrassantes. Nous ferons ça cette nuit.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "D'accord. Mais alors, faites en sorte que personne ne vous voie la traîner jusqu'au 'Protector’... Sinon, il faudra que je réponde à des questions gênantes.";
			link.l1 = "On ne laissera pas faire ça. On le fera cette nuit.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Venez après minuit. Elle sera ici. Et pour l'amour de Dieu, soyez prudents.";
			link.l1 = "Ne t'inquiète pas, "+npchar.name+", nous serons extrêmement attentifs.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Venez après minuit. Elle sera ici...";
				link.l1 = "D'accord.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = " Aurélie est prête. Vous pouvez l'emmener. ";
				link.l1 = "Parfait. Alors, en route.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Les jeunes gens, mais où... où allons-nous ?! C'est le navire des Rivadós ! Où est Éric ?!";
			link.l1 = "Eric s'est lié d'amitié avec Eddie Black, tu ne savais pas ?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Qu'est-ce que tu racontes, gamin ! Ouais, hein ? Mais Érik, il ne peut pas encadrer les Noirs !";
			link.l1 = "Eh ben dis donc ! Alors allons lui demander ce qu'il fiche ici, nom d'un diable !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Regardez donc qui nous rend visite ! "+GetFullName(pchar)+" en personne ! Heureux d'accueillir mon frère blanc, ha-ha ! Alors, qu'est-ce qui t'amène ?";
			link.l1 = "Salut à toi, "+npchar.name+"J'aimerais bien passer juste pour une chope de rhum, mais, j'ai bien peur d'avoir une affaire urgente à régler avec toi, ou plutôt avec Chimiseto.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Nous te sommes redevables, mon ami. Nous ferons tout ce qui est en notre pouvoir.";
			link.l1 = "D'accord, si tu veux. Parce que je n'ai plus personne sur qui compter.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "De laquelle de ces dames as-tu besoin d'aide, "+pchar.name+"?";
			link.l1 = "Je ne sais pas, tu es sérieux ou tu plaisantes, "+npchar.name+", mais je n'ai pas le cœur à rire. C'est Aurélie qui a besoin d'aide, bien sûr.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric ! ERIC ! Montre-toi, vieux filou ! C'est quoi ces manières ? Ramène tout de suite ton derrière maigre ici !";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Alors c'était pas des mensonges... Mes hommes m'avaient dit que cette vieille est complètement timbrée. Maintenant je vois qu'ils disaient vrai. Mais je ne comprends pas très bien ce que tu veux aux Rivares...";
			link.l1 = "Laisse-moi parler à Chimisetu, et tu comprendras tout...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;

		case "Chimset_1":
			dialog.text = "Parle, mon cher ami. Je suis prêt à t'écouter attentivement.";
			link.l1 = "Je serai bref, Chimisetu. Aurélie détient des informations dont Mary et moi avons besoin. Mais vu son état — dû, si je comprends bien, tout simplement à son âge — on ne peut ni les obtenir d'elle, ni être sûrs qu'elles seront fiables. J'ai entendu parler des miracles dont sont capables les chamans, qu'ils soient africains ou indigènes — c'est pourquoi je viens te demander de l'aide, Chimisetu.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;

		case "Chimset_2":
			dialog.text = "Je t'ai entendu, mon ami. Les chamans détiennent des pouvoirs mystérieux et mystiques, souvent incompréhensibles, même pour leurs propres semblables, et encore moins pour les Blancs. Certains appellent ça de la sorcellerie, d'autres — un miracle. Nous sommes capables de grandes choses — mais personne ne peut faire couler une rivière à l'envers... Ni l'arrêter.";
			link.l1 = "Qu'est-ce que tu veux dire, Chimisetu ?";
			link.l1.go = "Chimset_3";
		break;

		case "Chimset_3":
			dialog.text = "Je parle du fleuve du temps, mon ami. Ou du fleuve de la vie — comme tu préfères. Tu vois, tu as tout à fait raison : la racine du mal de cette pauvre femme vient précisément de ses années, et de rien d'autre.";
			link.l1 = "J'en ai entendu parler un peu. Je sais juste que ce n'est pas si rare que ça.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Tu as raison. Les gens de son âge s'égarent souvent dans les vallées des rêves, et parfois des cauchemars. Ils en reviennent, pour mieux y retourner ensuite – moins par leur propre volonté que poussés par des forces mystérieuses qui les y attirent. Avec le temps, la maladie s'aggrave – et alors, la personne ne se souvient plus ni d'elle-même, ni de ses amis.";
			link.l1 = "Donc, tu ne peux vraiment rien y faire, ouais, hein ?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Chasser la maladie – non. Ça, je n'en suis pas capable. Mais je peux faire autre chose...";
			link.l1 = "Quoi exactement ?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "Au moment où cette femme reprendra ses esprits, je ferai un rituel rapide, pour lequel je me préparerai à l'avance...";
			link.l1 = "Ça ne va peut-être pas l'arrêter, mais au moins ralentir la progression de la maladie ?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Pas vraiment. Il va lui forcer à puiser dans toutes ses forces vitales pour garder la raison le plus longtemps possible.";
			link.l1 = "Le plus longtemps possible, c'est combien ?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Cela ne dépend pas du rituel, mais de la personne. Certains tiennent une semaine, d'autres — un mois... J'ai entendu parler d'un homme qui a vécu sain d'esprit et avec toute sa mémoire pendant plus d'un an, presque... Et alors que tout le monde pensait qu'il était guéri, la maladie est revenue — et l'a emporté cette même nuit.";
			link.l1 = "Pour apprendre ce qu'il nous faut, une heure suffira. Quand pourras-tu faire le rituel, Chimisetu ?";
			link.l1.go = "Chimset_9";
		break;

		case "Chimset_9":
			dialog.text = "Je vais emmener la femme tout de suite, la conduire à la cale — là-bas, un sanctuaire a été aménagé... juste pour ce genre de choses. Ensuite, tout dépendra du moment où elle reviendra à elle... Mais je pense que d'ici l'aube, ce sera fait.";
			link.l1 = "Alors je ne vais pas vous déranger davantage. Et que ton... Dieu t'aide, Chimisetu.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Merci ! Aide-moi à emmener la femme blanche à la cale.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Tout s'est bien passé, frère blanc. On a réussi...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! Je ne savais pas que vous étiez revenus sur l'Île avec Mary ! Quelle agréable surprise !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Merci, Chimiset ! Je ne sais même pas comment te remercier...";
			link.l1.go = "Chimset_14";
			link.l2 = "Eh ben ça alors, Chimiset – t'as réussi ! J'en doutais pas une seconde, ouais, hein…";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Tous les Rivadans te seront à jamais redevables, mon ami ! Les portes du 'Protecteur' te seront toujours ouvertes.";
			link.l1 = "J'espère que je n'aurai plus à vous déranger… Mary, Aurélie, il faut qu'on retourne sur le 'Pluton’.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Tous les Rivadans te seront à jamais redevables, mon ami ! Les portes du 'Protecteur' te seront toujours ouvertes.";
			link.l1 = "J'espère que je n'aurai plus à vous déranger… Mary, Aurélie, il faut qu'on retourne sur le 'Pluton’.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "J'ai même oublié comment j'ai quitté ma cabine... Ah, cette vieillesse — la mémoire fout le camp complètement.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Alors, alors, jeune demoiselle, qu'est-ce que vous faites dans ma cabine ?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Aurélie, je...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Aurélie, je lui ai demandé de faire un peu de ménage ici pendant ton absence. Pas la peine que tu te casses le dos avec tes genoux mal en point...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Nettoyer ?! Toi...";
			link.l1 = "Jillian, merci pour ton travail. (à voix basse) On a réussi. Chimisette s'en est sorti.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Impossible...";
			link.l1 = "Comme tu vois. Et maintenant, s'il te plaît, laisse-nous parler.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Eh bien, les jeunes, merci d'avoir accompagné une vieille femme. J'ai bien peur que bientôt, je ne sorte plus du tout. Mes jambes, mes pauvres jambes...";
			link.l1 = "Si vous permettez, "+npchar.name+", on va rester chez vous – juste pour un petit moment. Mary et moi, on a quelque chose de très important à vous dire.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Si je n'ai pas encore à me traîner sur un autre navire, je vous aiderai comme je peux. Je vous écoute.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Aurélie, je veux que tu me parles de mes parents. Et du jour où je suis née. C'est bien arrivé ici, sur l'Île, n'est-ce pas ? Donald affirme que c'est le cas, mais il n'était pas encore là à l'époque, alors il ne peut pas en être sûr. Toi, en revanche, tu vis ici depuis bien plus longtemps que lui, hein ! Depuis plus de vingt ans, n'est-ce pas ?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Doucement, doucement, ma fille, ne parle pas si vite, je t'en prie ! Sinon, je n'arrive pas à te suivre...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Je vois, ouais, hein. Bon, on recommence encore une fois...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Ne t'en fais pas, Mary, je ne suis pas si mal en point pour l'instant, ha ha… J'ai bien entendu ce que tu m'as dit. Mais, puisque je vis vraiment sur l'Île depuis plus longtemps que tout le monde, j'espère que tu respecteras mon âge et que tu feras preuve de compréhension…";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Mais bien sûr, Aurélie ! Comment as-tu pu penser autrement ?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ah, je regarde les jeunes d'aujourd'hui et… non, non, on ne se comportait pas comme ça avec les aînés à notre époque. Mais toi, tu n'es pas concerné, bien sûr. Je voulais juste dire qu'on s'en sortira mieux si je réponds à tes questions une par une, plutôt que toutes en même temps...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Je comprends, Aurélie. Comme tu voudras, ouais, hein ? Alors, tu étais sur l'Île quand je suis née ? Si c'est bien ici que ça s'est passé, bien sûr...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Je suis arrivée sur l'Île en 1633, et ce jour-là me revient parfois en cauchemar. La tempête, notre 'Reprisal' — un flûte sur lequel mon mari et moi faisions route vers la Floride — secoué par les vagues, prêt à chavirer à tout moment, et nous récitons toutes les prières qu'on connaît et on en invente d'autres... Puis un craquement, et...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Alors, tu t'es retrouvée ici cinq ans avant ma naissance, ouais, hein.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "À peu près. À l'époque, tout était un peu différent ici — le 'San Jeronimo' flottait encore, l'anneau extérieur de navires était une fois et demie, voire deux fois plus petit... Et encore, tous les navires ne flottent pas ! Je vais vous dire une chose, les jeunes : si vous regardez le fond par temps clair, vous serez horrifiés de voir combien d'épaves gisent là-dessous...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Ce qui nous intéresse, c'est le navire sur lequel mes parents sont arrivés ici. Avec moi… ou sans moi ?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Avec toi, ma fille, avec toi.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Alors, je suis vraiment née sur le continent, hein ?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Non, je voulais dire 'avec toi' dans un autre sens. Tu étais dans le ventre de ta mère et tu es née une semaine plus tard.";
			link.l1 = "Vous trouvez ça drôle, Aurélie ?";
			link.l1.go = "Oreli_32";
			link.l2 = "Et avec les années, vous n'avez pas perdu votre sens de l'humour, Aurélie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Bon, je me moque de moi bien plus souvent que des autres. Désolée, Mary, je ne voulais pas te blesser.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Oh, tu sais, je me moque bien plus souvent de moi-même que des autres. Pardon, Mary, je ne voulais pas te blesser.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Tout va bien, Aurélie. Vas-y, continue, ouais, hein ? Qu'est-il arrivé à mes parents après ma naissance ?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Après ? Ma chère, le simple fait qu'ils aient tous les deux survécu jusque-là — c'était un véritable miracle ! Quelle terrible tempête faisait rage cette nuit de juin ! Quand, au matin, une chaloupe a amené ta mère jusqu'à l'anneau intérieur, peu de gens ont cru ce qu'ils voyaient — qu'une femme enceinte, sur le point d'accoucher, ait survécu à un tel naufrage. La pauvre Teresa, je m'en souviens comme si c'était hier...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Thérèse ? C'est comme ça qu'elle s'appelait ?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Oui, c'est ainsi qu'elle s'est présentée — et c'était à peu près tout ce qu'elle a dit. À la fin de la journée, elle est tombée dans un délire qui a duré jusqu'à l'accouchement. Personne n'était certain qu'elle parviendrait à accoucher, et encore moins que l'enfant naîtrait vivant — après tout ce qu'elle avait enduré. Mais Teresa a tenu bon. Elle a réussi — puis elle a rendu l'âme. Que Dieu ait son âme...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Maman est morte, et je suis restée avec mon père ? Mais pourquoi alors tout le monde disait que j'avais été élevée par Éric Udet ? Et...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, chérie, je t'en prie… Ne m'assaille pas avec autant de questions…";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Pardon, Aurélie, je me suis laissée emporter, ouais, hein ? Mon père, lui aussi, il a survécu à un naufrage ?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Ton père... Tu sais, je ne peux pas dire grand-chose sur ton père – si ce n'est que je ne souhaiterais un tel père à personne. Quelques jours après ta naissance, il a disparu, te laissant livré à toi-même. Tu as eu de la chance qu'Éric ait un cœur aussi bon et tendre – comme un vieux biscuit ramolli dans une chope de grog...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Dis-moi au moins comment il s'appelait, ouais, hein !";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Oh là là... Était-ce Jeffrey ou John, si seulement je pouvais m'en souvenir...";
			link.l1 = "Alors, vous ne vous souvenez pas ? C'est bien ça, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Vous doutez de mes paroles, jeune homme ?!";
			link.l1 = "Chut, "+npchar.name+", du calme. Je ne voulais pas vous blesser. C'est juste que j'ai eu l'impression que vous vous souveniez plutôt bien de ces jours-là, c'est tout.";
			link.l1.go = "Oreli_45";
			link.l2 = "Je n'ai aucun doute, "+npchar.name+". J'essaie simplement de retenir tous les détails correctement — rien de plus. Mais tout ce fouillis complique un peu les choses.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "La mémoire est une dame capricieuse, "+pchar.name+",   très   sélective.   Surtout   après   toutes   ces   années.   Il   est   difficile   d'oublier   Thérèse   –   je   l'ai   vue   souffrir   toute   la   semaine !   Oh,   comme   je   la   plaignais !";
			link.l1 = "Et son mari, il n'était pas à ses côtés ?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "La mémoire est une dame capricieuse, "+pchar.name+",   très   sélective.   Surtout   après   tant   d'années.   Difficile   d'oublier   Thérèse —   je   l'ai   vue   souffrir   toute   la   semaine !   Oh,   comme   je   la   plaignais !";
			link.l1 = "Et son mari, il n'était pas à ses côtés ?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Très rarement. Presque toute la semaine, il disparaissait quelque part – à la recherche de remèdes et de potions, qui étaient alors en grand manque sur l'Île...";
			link.l1 = "Alors, c'était un bon mari – puisqu'il a essayé d'aider sa femme.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Peut-être qu'il était un bon mari. Je n'ai jamais prétendu le contraire, permettez-moi de le souligner. N'essayez pas de me brouiller l'esprit, jeune homme !";
			link.l1 = "Je n'y ai même pas pensé, je t'assure, "+npchar.name+". Il est juste évident que vous n'avez pas la meilleure opinion de lui. Et le fait que vous ne vous souveniez même pas de son nom...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "J'ai aperçu cet homme à peine un instant dans la pénombre de la cabine du 'Cérès Smithy', là où vit maintenant Herr Jürgen. Il ne venait que la nuit, et je me souviens très vaguement de son visage. Quant à son prénom — personne ne l'appelait jamais par son prénom, seulement par son nom de famille. Casper par-ci, Casper par-là...";
			link.l1 = "J'ai compris, "+npchar.name+". Donc, Mary est née, et quelques jours plus tard il a disparu sans laisser de trace. On l'a tué ?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Question difficile, jeune homme. Vous voyez, ici, il est plutôt compliqué de garder quoi que ce soit secret – tout est visible pour tout le monde. Dès qu'il y a une nouvelle dispute – même à l'intérieur des navires – le lendemain, toute l'Île est déjà au courant.";
			link.l1 = "Pas étonnant.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "On ne retrouve pas toujours les corps des victimes — les types expérimentés les coulent en attachant des boulets doubles aux bras et aux jambes, ou en y liant des boulets ou des pierres. Et les crabes au fond finissent le travail. Mais les effets personnels des morts refont surface, tôt ou tard.";
			link.l1 = "Du fond ?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Bien sûr que non ! Je voulais dire qu'on tombe parfois sur des objets – une bague, un pistolet gravé, un sabre de récompense… On ne pose pas souvent de questions à ce sujet. On ne ramènera pas la personne, et des conflits en plus, ça ne sert à rien.";
			link.l1 = "Est-ce que Geoffrey ou John Casper avaient des objets reconnaissables ?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", que Dieu vous protège — je ne me souviens même plus de son nom, et vous me posez ce genre de questions ! S'il s'est passé quelque chose, je n'ai rien entendu sur le fait que cet objet ait fini entre les mains d'un autre habitant de l'Île. À l'époque, je travaillais comme serveuse à la taverne, et peu de rumeurs m'échappaient. Mais ça ne veut pas dire que je savais absolument tout.";
			link.l1 = "Quand on dit que des gens disparaissent sans laisser de traces, on sous-entend généralement qu'ils ont été tués. Mais dans le cas de monsieur Casper, vous n'en êtes manifestement pas si sûr...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Je dis juste que  'disparu' ne veut pas forcément dire 'mort'. Surtout à cette époque, quand des tartanes de contrebandiers et de receleurs faisaient sans cesse la navette entre l'Île et Cuba... Vous savez, je ne me souviens pas de ses traits, mais son regard, par contre... C'était le regard d'un homme qui ne se perdrait nulle part. Ou, en tout cas, qui en était profondément convaincu.";
			link.l1 = "Les tartanes, les tartanes... Rien n'est impossible. Si on connaissait son nom, on pourrait fouiller les archives coloniales de l'époque. Mais ce serait bien plus simple si on avait le type et le nom du navire sur lequel il est 'arrivé' ici.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "Et pourquoi tu me regardes comme ça, jeune homme ? Tu crois que je vais m'en souvenir ?";
			link.l1 = "On l'espère, "+npchar.name+" - étant donné tout ce que vous nous avez déjà raconté.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hmm... J'ai de gros doutes à ce sujet.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Peut-être que vous voulez aussi savoir combien de canons il avait et de quel calibre ? Mon cher, vous savez combien de navires ont sombré ici au fil des ans ? Et vous pensez que je me souviens de chacun d'eux ? En plus, à peine quelques personnes ont survécu à ce naufrage – ce bateau n'a même pas tenu une journée à flot, vous savez...";
			link.l1 = "Je vois... C'est normal, vingt ans ont passé. Merci de ne pas avoir oublié au moins ce qu'on nous avait raconté.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Peut-être que vous voulez aussi savoir combien de canons il avait et de quel calibre ils étaient ? Mon cher, savez-vous combien de navires ont sombré ici au fil des ans ? Et vous pensez que je me souviens de chacun d'eux ? En plus, il n'y a eu que quelques survivants de ce navire-là – il n'a même pas tenu une journée à flot, vous savez...";
			link.l1 = "C'est clair… Je comprends, vingt ans se sont écoulés. Merci de ne pas avoir oublié au moins ce qu'on nous avait raconté.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "J'espère que vous ne plaisantez pas et que vous n'essayez pas de vous moquer d'une vieille femme dont la mémoire est devenue passoire.";
			link.l1 = "En aucune façon, "+npchar.name+"Vous nous avez vraiment beaucoup aidés. Remettez-vous bien. Bon, nous allons y aller.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Alors, Thérèse... C'était son nom. Ma pauvre maman, ouais...";
			link.l1 = "Eh bien, au moins maintenant on sait de qui tu tiens toute cette force et cette obstination. Une femme enceinte sur un navire en perdition... Rien que d'y penser, ça me donne des frissons.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Mais qu'est-ce qu'elle faisait dans cet état sur ce navire, "+pchar.name+"?! Faut vraiment être folle pour oser faire un truc pareil !";
			link.l1 = "Seul ton père peut répondre à cette question – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Tu as décidé de te rappeler tous les prénoms anglais qui commencent par 'J' ? Aurélie n'a cité que Geoffrey et John, ouais, hein ?";
			link.l1 = "Peut-être qu'elle ne s'est tout simplement pas souvenue du reste, comme moi ? Tu sais, l'âge et tout ça...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", tu penses...";
			link.l1 = "Je ne ferais pas entièrement confiance à sa mémoire pour l'instant. Mais même si c'est vrai, il nous faudra consulter non pas les archives coloniales — mais celles de la flotte pour l'année 1638, et c'est bien plus compliqué : ce sont des informations classifiées, surtout quand il s'agit d'officiers. Et j'ai de sérieux doutes qu'un simple matelot ait pu embarquer sa femme à bord.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "D'un autre côté, trouver des informations sur un officier, c'est bien plus facile que sur un simple marin.";
			link.l1 = "Si on connaît le nom du navire. Ou son nom complet. Et pas juste 'Jeffrey ou John ou, à la rigueur, Jack...’. On aura encore de la chance si c'était un navire militaire. Chez les marchands, avec les listes d'équipage, c'est bien pire.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Mais qu'est-ce qu'on va faire alors, "+pchar.name+"? Parler encore une fois à Aurélie ? On a déjà tiré d'elle tout ce qu'on pouvait, tu ne trouves pas, ouais, hein ?";
			link.l1 = "Pas avec Aurélie. Avec Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "Et comment il va nous aider ? Il a bien dit qu'en 1638, il n'était même pas sur l'Île de la Justice, ouais, hein ?";
			link.l1 = "Mais il y avait d'autres narvals ici, non ?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Je ne comprends pas trop où tu veux en venir.";
			link.l1 = "Tu verras, ma chère, tu verras. Il y a encore un fil à tirer. Viens.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Ah, vous revoilà ! Alors, comment avancent vos recherches ?";
			link.l1 = "Bonjour, "+npchar.name+". Ça pourrait aller mieux – pour l'instant, on erre comme dans cette grotte pleine de mystères et d'énigmes. Mais on sent que la sortie est déjà proche.";
			link.l1.go = "Grinspy_32";
			link.l2 = "Et salut à toi, "+npchar.name+"Mieux que ce qu'on aurait pu imaginer au début. La situation... n'est pas si désespérée que ça.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Content de l'entendre. Vraiment. Mais vous avez encore besoin de quelque chose, tous les deux, n'est-ce pas ? Alors, qu'est-ce que vous avez découvert ?";
			link.l1 = "Mary est née ici, sur l'Île, en juin 1638. Sa mère, Teresa, est morte juste après l'accouchement. Son père – un certain Casper – a disparu sans laisser de traces quelques jours après la naissance de Mary. On ne sait rien de lui, à part que son prénom commence par un 'J’. Certains pensent qu'il n'a pas fini en nourriture pour crabes dans les bas-fonds du coin, mais qu'il a quitté l'Île à bord d'une des tartanes des contrebandiers…";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Grinspy_33":
			dialog.text = "Content de l'entendre. Vraiment. Mais vous avez encore besoin de quelque chose, tous les deux, n'est-ce pas ? Alors, qu'est-ce que vous avez découvert ?";
			link.l1 = "Mary est née ici, sur l'Île, en juin 1638. Sa mère, Teresa, est morte juste après l'accouchement. Son père – un certain Casper – a disparu comme par magie quelques jours après la naissance de Mary. On ne sait rien de lui, à part que son prénom commence par un 'J’. Certains pensent qu'il n'a pas fini en nourriture pour crabes dans les bas-fonds du coin, mais qu'il a quitté l'Île à bord d'une des tartanes des contrebandiers…";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "Et il a abandonné sa fille ? C'est étrange, comme geste.";
			link.l1 = "C'est bien ça. Mais personne, à part ce fameux monsieur J., ne pourra l'expliquer.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "Et vous pensez qu'il est encore en vie ? C'est pour ça que vous le cherchez ?";
			link.l1 = "Pas seulement pour ça. Nous voulons savoir qui il était, comment il vivait. Pour Mary, c'est très important.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hm, je comprends. Et je suis désolée de ne vraiment rien pouvoir faire pour vous aider...";
			link.l1 = "En fait, tu peux. Dis-moi, les narvals tiennent bien une sorte de registre des navires perdus près de l'Île, non ?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Je ne comprends pas trop ce que tu veux dire, "+pchar.name+".";
			link.l1 = "Grinspie, Grinspie... N'oublie pas que si tu peux encore réchauffer ton derrière sur cette chaise, c'est uniquement grâce à moi. Alors sois gentil – ne mets pas ma patience à l'épreuve.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Tu comprends bien, Donald. Et au nom de notre amitié, tu ne vas pas essayer de tourner autour du pot.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hmm...";
			link.l1 = "Des navires s'échouent de temps en temps sur l'anneau extérieur. Certains coulent immédiatement, d'autres restent à flot quelque temps — on les fouille et on en récupère tout ce qui a de la valeur. Je ne sais pas pour les Rivares, mais je doute que les Narvals se battent pour chaque babiole trouvée à bord — ils mettent probablement tout en commun, procèdent ensuite à un inventaire complet, et ce n'est qu'après qu'ils se partagent le butin.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "Des navires s'échouent de temps en temps sur l'anneau extérieur. Certains coulent immédiatement, d'autres restent à flot quelque temps — on les fouille et on en récupère tout ce qui a de la valeur. Je ne sais pas pour les Rivares, mais je doute que les Narvals se battent pour chaque babiole trouvée à bord — ils mettent probablement tout en commun, procèdent ensuite à un inventaire complet, et ce n'est qu'après qu'ils se partagent le butin.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "Tu n'es pas bête, "+pchar.name+"Contrairement à beaucoup ici. Ouais, c'est à peu près comme ça que ça se passe. Personnellement, cette paperasse me sort par les yeux, mais on le faisait déjà à l'époque d'Alan Milroe et de ceux qui dirigeaient le clan 'Narval' avant lui. On tient ce genre de registres – et même plus : on note aussi les navires que les Rivadans ou les pirates ont atteints avant nous. Mais dans ces cas-là, évidemment, on n'a aucune idée de qui était à bord, ni de ce qu'il y avait…";
			link.l1 = "D'après le fait que les parents de Mary ont été amenés après le naufrage sur le 'Cérès Smithy', c'est donc les Narvals qui ont trouvé leur navire. Donc, il doit y avoir un registre correspondant.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Peut-être bien. Je ne peux pas l'affirmer. Et je ne pourrai pas.";
			link.l1 = "Maintenant, c'est moi qui ne comprends plus ce que tu veux dire, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Les registres des navires perdus. Quand Leighton Dexter est devenu Amiral après le départ de Dodson, il nous a pris ces documents.";
			link.l1 = "Il a juste pris et confisqué ? Et toi, t'as rien dit ?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "D'abord, il était plutôt poli. Ensuite, il a promis de les rendre bientôt. Et puis... qu'est-ce que j'en ai à faire de ces papiers, hein ?";
			link.l1 = "Pas les notes les plus inutiles, hein.";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Je te l'ai dit, ce n'est qu'une tradition, principalement destinée à empêcher les membres de notre clan de s'égorger pour le butin des navires. Un navire s'échoue, on en retire tout ce qu'on peut, on fait l'inventaire, on partage certaines choses, on en cache d'autres dans nos cales — et voilà. Pourquoi remplir les coffres ? Il y avait un peu de place libre — je devrais peut-être même remercier l'Amiral pour ça.";
			link.l1 = "Bon, d'accord. Alors, cap sur 'San Augustin’. Mais peut-être qu'on passera encore te voir, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;

		case "WildRose_Dexter_1":
			dialog.text = "Ah, "+pchar.name+" Entre, entre. Tu viens me voir pour une raison, mon ami, ou c'est juste une visite de courtoisie ?";
			link.l1 = "Cette fois, c'est du sérieux. Disons que c'est… personnel.";
			link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Dexter_2":
			dialog.text = "Et assez important pour toi – à en juger par ton air tout bouleversé.";
			link.l1 = "Vraiment ? Je dirais plutôt fatigué. J'ai pas mal arpenté tes terres ces derniers jours. Mes articulations commencent à me rappeler leur existence — et moi qui pensais naïvement que ça n'arrivait qu'aux vieux comme toi.";
			link.l1.go = "WildRose_Dexter_3_1";
			link.l2 = "Je suis juste un peu essoufflé, c'est tout. Tu vois, je ne fais pas que rester assis dans un fauteuil. Mais toi, on dirait que tes jambes ne te portent plus du tout, ha-ha-ha !";
			link.l2.go = "WildRose_Dexter_3_2";
		break;

        case "WildRose_Dexter_3_1":
            dialog.text = "Et tu t'es jamais demandé pourquoi je reste collé à cette chaise, hein, héhé ? Tu sais, ta vision du monde peut vraiment changer quand tu piges que la santé, tu peux pas l'acheter, même avec toutes les richesses de cette Île.";
            link.l1 = "Drôle, c'est justement pour ça que je suis venu te parler.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "Et tu t'es jamais demandé pourquoi je reste vissé à cette chaise, hein, héhé ? Tu sais, la vision du monde peut vraiment changer quand tu comprends que la santé, tu peux pas l'acheter, même avec toutes les richesses de cette Île.";
            link.l1 = "C'est drôle — c'est justement de ça que je suis venu te parler.";
			link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "Ma santé, tu veux dire ?";
            link.l1 = "Non, des richesses de l'Île. Et pour être un peu plus précise, de leur inventaire. Et pour être tout à fait précise, des journaux qui contiennent ces inventaires.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Kof-kof... "+pchar.name+", je ne comprends pas trop de quoi tu parles ?";
            link.l1 = "Il n'y a pas si longtemps, tu as récupéré auprès des narvals les registres des navires échoués sur l'Île...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Alors, ce crétin de Greenspy a décidé de t'envoyer à leur poursuite ? Quel culot.";
            link.l1 = "Pas du tout, "+npchar.name+", Donald n'y est pour rien. C'est moi qui suis venu le voir avec cette question, et il m'a envoyé vers toi. Mais ta réaction, je dois l'avouer, m'a bien amusé. Tu veux pas me dire pourquoi tu as eu besoin des registres des narvals ?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Pourquoi tu ne me le dirais pas, hein ? Comme tu t'en doutes sûrement, les navires eux-mêmes, je m'en fiche. Et les trésors dans leurs cales — franchement, pareil. Y'en a assez pour tout le monde, tant qu'on devient pas trop gourmands — c'est comme ça que je vois les choses. Ce qui m'intéresse vraiment, c'est les armes : mousquets, sabres... et les canons, surtout. Oui, ces malins en démontent même parfois. Les Noirs crétins n'en sont pas capables, mais les Narvals, eux...";
			link.l1 = "Et tu as décidé de voir à quel point les gens de Grinspie sont prêts pour une nouvelle vague d'affrontements ?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "Et insinuer que moi et mes gars, on garde l'œil ouvert. Le message est assez clair, mais vu le cirque que Donald a fait avec ces exercices, je peux très bien imaginer qu'il s'est mis en tête que son argent m'intéresse.";
            link.l1 = "Ouais, je vois bien que la situation ne tourne pas vraiment comme tu l'espérais. Et Rivados ? Le Noir Eddie ne te cause pas de soucis ?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Ces sales Noirs – pas étonnant que le Requin les détestait autant.";
            link.l1 = "Donc, ça te plaît.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "C'est bien ça le problème, que non, que le diable m'emporte ! Les Noirs se sont calmés, ils restent planqués sur leurs navires...";
            link.l1 = "Et alors, qu'est-ce qui te dérange, bon sang, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Comment t'expliquer, "+pchar.name+"... Tu vois, c'est comme le vent en pleine mer. Parfois il est faible, parfois il souffle fort, et parfois c'est carrément la tempête. Mais quoi qu'il arrive, le vent pousse le navire en avant, et un bon capitaine sait toujours le maîtriser.";
            link.l1 = "Une brise légère vaut toujours mieux qu'une tempête furieuse.";
            link.l1.go = "WildRose_Dexter_12";
        break;

       case "WildRose_Dexter_12":
			dialog.text = "Oui. Mais parfois, il n'y a tout simplement pas de vent. Mer d'huile — et là, aucun skipper ne peut y faire quoi que ce soit. Tu restes juste assis sur le gaillard arrière, tu regardes l'eau immobile, et tu te demandes ce que le diable va bien pouvoir se passer ensuite. C'est pareil avec Eddie et son pote Chimisetu — ils préparent quelque chose, je le sens dans mes tripes, et ça ne présage rien de bon, par le tonnerre !";
			link.l1 = "Tu devrais peut-être te bouger un peu et aller parler à Edward en face. Ou mieux encore, vous réunir tous les trois, avec Donald aussi, et mettre les choses à plat franchement. Ce serait toujours mieux que de plonger à nouveau l'Île dans un bain de sang. Enfin bon… Revenons à ce qui m'amène.";
			link.l1.go = "WildRose_Dexter_13";
		break;

		case "WildRose_Dexter_13":
			dialog.text = "Alors, tu t'intéresses aux trésors des Narvals, j'ai raison ? Qu'est-ce que tu veux y trouver ?";
			link.l1 = "Je cherche des listes de navires perdus ici. Plus précisément — pour l'année 1638. On essaie de trouver des informations sur les parents de Mary. On a une idée assez claire concernant sa mère — mais pour ce qui est de son père, c'est une autre histoire. On ne sait presque rien de lui, même pas son nom, et notre seul espoir, c'est le nom du navire qui s'est écrasé sur l'anneau extérieur en juin 1638...";
			link.l1.go = "WildRose_Dexter_14";
		break;

        case "WildRose_Dexter_14":
            dialog.text = "L'affaire est noble – moi aussi, autrefois, je me suis tourmenté en pensant à qui pouvait bien être mon propre père. Mais je ne peux pas vous aider, ouais, hein ?";
            link.l1 = "Et pourquoi donc, si ce n'est pas indiscret ?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Tu ne me caches rien, "+pchar.name+". Ce n'est pas du tout à cause de moi, mais à cause de Donald – il ne m'a remis que des papiers datant de 1651. J'ai demandé ce qu'il en était des documents plus anciens, au moins pour la décennie précédente – et il m'a répondu qu'il n'y en avait pas d'autres. C'est tout ce qu'il a hérité d'Alan Milrow à ce sujet – c'est ce qu'il a dit.";
            link.l1 = "Je ne pense pas qu'il avait de raisons de mentir.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Je pense pareil, mon ami. Vu qu'il m'a donné les nouveaux registres sans poser de questions. En plus, j'ai eu l'impression qu'il était même, d'une certaine façon, content de se débarrasser de ces vieilleries… Qui sait, peut-être que Milroe s'est tout simplement débarrassé des papiers des décennies passées… Il les a brûlés, ou alors peut-être…";
            link.l1 = "Non, c'est pas possible.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Non, ce n'est pas possible. Alan n'aurait jamais fait ça.";
            link.l1 = "Pourquoi tu en es si sûre, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Je croyais qu'il était plutôt du genre à manier le couteau ou la hache, qu'à s'occuper de toute cette paperasse. Je suis surpris qu'il sache même lire.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
			dialog.text = "Il accordait beaucoup d'importance à tout ce qui concernait les archives de l'Île. Il les considérait comme une part de son histoire. Et l'histoire — pas seulement celle de ce lieu — c'était une véritable passion pour Alan, oui. Il étudiait tous les documents historiques à sa portée, les livres… Parfois, je me disais qu'il aurait fait un bien meilleur érudit qu'un bretteur — je le lui ai même dit une fois.";
			link.l1 = "...";
			link.l1.go = "WildRose_Dexter_18";
		break;

       case "WildRose_Dexter_17_2":
			dialog.text = "Il traitait avec beaucoup de soin tous les écrits concernant l'Île. Il les considérait comme une partie de son histoire. Et l'histoire, pas seulement celle de cet endroit d'ailleurs, était une vraie passion pour Alan, ouais, hein ? Il étudiait tous les documents historiques et livres auxquels il avait accès… Parfois, je me disais qu'il aurait fait un bien meilleur savant qu'un bagarreur — une fois, je le lui ai même dit.";
			link.l1 = "Peut-être qu'il aurait vraiment dû préférer les lunettes, le papier et la plume à l'épée et au pistolet — il foulerait peut-être encore les planches pourries des navires d'ici. Mais si Milroe tenait tant aux archives, qu'est-ce qu'il a fait de tous ces documents ? Je veux bien croire qu'il ait pu ruiner un papier avec de l'encre par accident — mais il y en avait des dizaines, voire des centaines, non ?";
			link.l1.go = "WildRose_Dexter_18";
		break;

        case "WildRose_Dexter_18":
            dialog.text = "Je sais seulement qu'il gardait ces documents plus précieusement que tout au monde. Peut-être que quelqu'un les a volés, ou alors il les a donnés à quelqu'un lui-même...";
            link.l1 = "Volé ? Qui aurait bien pu avoir besoin d'informations sur des navires éventrés de la dunette à la quille depuis longtemps ? Les avoir donnés, c'est bien plus probable, mais à qui, et pourquoi ?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "À un autre passionné d'histoire, ha ha ha ! Je suis d'accord avec Charles – je ne vois vraiment pas qui d'autre aurait pu avoir besoin de ces vieux papiers.";
            link.l1 = "Quelqu'un, pourtant, en a eu besoin. Faudra réfléchir à tout ça. Bon, "+npchar.name+", on ne va pas te déranger plus longtemps. On se reverra.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", content de te revoir. Comment ça se passe avec Mary ?";
			link.l1 = "Et nous sommes ravis de te voir, "+npchar.name+". Mais comment ça va se passer entre nous - ça dépendra de toi.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Un début de conversation intrigant, je dois l'admettre. Et un peu effrayant, vu l'expression de vos visages.";
			link.l1 = "N'aie pas peur, "+npchar.name+", ce n'est pas de ta faute. On est juste un peu fatigués de courir sur ces épaves grinçantes. Et puis, il fait lourd aujourd'hui, tu ne trouves pas ?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Cette chaleur ne nous donne pas vraiment de forces. Et on a dû courir partout sur l'Île pour te trouver — on a besoin de ton aide.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Euh, ouais, une petite brise serait la bienvenue maintenant. Alors, que puis-je faire pour vous ?";
			link.l1 = "Tu vois, Mary et moi avons lancé une enquête pour faire la lumière sur des événements vieux de vingt ans.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Euh, ouais, une petite brise légère ne serait pas de refus, hein ? Alors, qu'est-ce que je peux faire pour vous ?";
			link.l1 = "Tu vois, Mary et moi avons lancé une enquête pour faire la lumière sur des événements vieux de vingt ans.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Ça a l'air captivant. Et de quoi s'agit-il ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Mes parents, Antonio. Charles et moi, on essaie de découvrir qui ils étaient. Et ce qui leur est arrivé. Ma mère est morte en me mettant au monde, ça, on l'a déjà appris. Mais pour mon père, c'est pas si simple...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "Tu es née en quelle année, rappelle-moi...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "En 1638. En juin.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "J'avais à peine douze ans, Mary. Je ne me souviens pas très bien de cette époque. Bien sûr, il y a quelques souvenirs qui me reviennent, mais pour être honnête, c'est un peu difficile d'en faire un tout cohérent. Désolé, mais je doute de pouvoir t'aider...";
			link.l1 = "Ce n'est pas tout à fait ça qu'on attend de toi, Antonio. Mais si jamais tu te souviens de quelque chose de ce jour-là, quand Mary est venue au monde, on t'en sera vraiment reconnaissants.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Alors, comment puis-je vous aider, "+pchar.name+"?";
			link.l1 = "Tu m'as dit que tu t'intéressais à l'histoire. À l'histoire du monde en général, et à celle de l'Île en particulier.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "C'est vrai. J'ai lu toutes sortes de livres, j'ai étudié tous les manuscrits que j'ai pu trouver...";
			link.l1 = "C'est justement des manuscrits qu'il s'agit. À part toi, il n'y avait qu'une seule personne sur l'Île qui s'intéressait à l'histoire autant que toi...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milroe. Ouais, on en a parlé, quand il n'était pas occupé à élaborer des plans pour anéantir les Rivares, puis les pirates. C'était un gars intelligent, vraiment pas ordinaire.";
			link.l1 = "Je n'en doute pas — c'était un type sacrément capable. Il avait quelque chose qui pourrait nous être utile. Quelque chose qui n'a aucune valeur pratique pour les gens de l'Île de la Justice, sauf pour vous deux. Des registres des navires échoués près de l'Île, contenant aussi la description des cargaisons récupérées et, peut-être, les noms des passagers...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "C'est bien ça.";
			link.l1 = "Alors, tu les as vus ?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Je ne les ai pas seulement vus — j'ai recopié les informations qu'ils contenaient dans mes propres notes. Lors d'une de nos conversations, il a mentionné l'existence de ces registres, et je lui ai demandé de me les prêter pour les étudier — j'essaie de compiler une sorte de Chroniques de l'Île de la Justice, et ces documents m'ont été très utiles. Alan était enthousiasmé par mon idée — écrire l'histoire de cet endroit. Cela dit, il ne m'a pas donné tous les registres, il a gardé ceux des années 1650, mais à l'époque, le reste me suffisait.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "Il y a bien des registres pour l'an 1638, non ? Dis-moi qu'il y en a, ouais, hein !";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "J'ai toute une pile de ces journaux – ça remonte même à 1620. C'est à ce moment-là, d'après Alan, qu'on a commencé à les tenir. Et ouais, il y a aussi l'année 1638 dedans, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Tu nous laisseras les consulter ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "On dirait que je n'ai pas vraiment le choix, ha ha ha ! Une seconde. Ils sont tous là, dans le tiroir du bas de cette armoire.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Je vous en prie. Installez-vous, explorez...";
			link.l1 = "On va s'en occuper.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Tiens, "+pchar.name+", regarde, ouais, hein ! Joshua et Teresa Casper ! J'arrive pas à y croire – on a réussi, on a réussi, ouais, hein ! Et le nom du navire – 'Wrangler' ! Maintenant on peut tout découvrir sur mon père – qui il était, comment il s'est retrouvé ici...";
			link.l1 = "J'ai peur, "+npchar.name+", tu es trop pressé... Ça pourrait ne pas être aussi simple qu'il y paraît. Le navire de Sa Majesté... Il va falloir réfléchir à qui pourrait nous aider à obtenir des informations des archives de la Marine Royale...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Réfléchissons ! On réfléchira et on obtiendra, "+pchar.name+" ! Le plus dur est déjà derrière nous, ouais, hein !";
			link.l1 = "Peut-être que ça vaudrait aussi le coup de parler aux messieurs Young et Friddicks. Cela dit, je ne me souviens pas avoir vu de tels hommes sur l'Île.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Parce qu'il n'y en a pas ici, "+pchar.name+". Ces deux-là sont morts la nuit suivante après avoir été sauvés avec les Casper.";
			link.l1 = "Curieux. Une femme enceinte a survécu encore une semaine, alors que deux marins de la Flotte Royale sont morts subitement...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Ils étaient déjà mauvais, si je me souviens bien. Maintenant je m'en rappelle, "+pchar.name+" - j'étais justement pas loin du 'Cérès Smithy' quand ils les ont fait monter à son bord... Ouais, j'étais sur l’'Esmeralda' – avec Aurélie Bertin, il me semble. Et puis il y avait aussi Chimiset – le chaman de ces païens noirs, venu pour une raison obscure à la boutique. Au début, j'ai cru que ces deux marins étaient déjà morts – mais ils ont rendu l'âme seulement un jour plus tard...";
			link.l1 = "Eh bien, on n'y peut rien. Mais on a déjà appris pas mal de choses. Merci pour ton aide, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "Je n'y suis pour rien, "+pchar.name+". Tout ça, c'est grâce à Alan, c'est son mérite – peu de ces cuirassiers auraient pu comprendre toute la valeur de ces écrits. Et pourtant, c'est justement grâce à de tels documents que l'histoire se reconstitue !";
			link.l1 = "J'espère qu'un jour, Mary et moi, on lira tes Chroniques, l'ami. Tiens, prends le journal, ne le perds pas. Bon, il est temps pour nous d'y aller. Peut-être qu'on se reverra, camarade.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Parce qu'il n'y en a pas ici, "+pchar.name+". Ces deux-là sont morts la nuit suivante après avoir été sauvés avec les Casper.";
			link.l1 = "Curieux. Une femme enceinte a survécu encore une semaine, alors que deux marins de la Flotte Royale sont morts subitement...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Content de te revoir, mon ami. Qu'est-ce qui t'amène ?";
			link.l1 = "Pour te demander, "+npchar.name+"... Enfin, c'est plutôt une question.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Pose ta question. Ou fais ta demande. Je ferai tout mon possible pour t'aider.";
			link.l1 = "D'accord. Depuis combien de temps tu vis sur l'Île ?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Des dizaines et des dizaines d'années, mon ami. Je suis arrivé ici enfant, mais déjà assez malin — à bord d'un navire négrier. Mon histoire ne diffère guère de beaucoup d'autres que tu as pu entendre ici. Une tempête, un naufrage... Le galion anglais dont la cale me servait de prison n'a même pas atteint l'anneau extérieur : il s'est brisé en deux en heurtant un des récifs, où la vague l'avait projeté.";
			link.l1 = "Comment as-tu survécu ? Les récifs sont quand même assez loin de l'anneau extérieur, et rejoindre la côte depuis là-bas, avec des vagues de tempête… c'est, disons-le franchement, pas une mince affaire…";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Les dieux étaient de mon côté cette nuit-là. J'ai réussi à me libérer de mes chaînes, puis à m'accrocher à un débris de ce qui avait été une chaloupe. Un compagnon de tribu, Asana, était avec moi – ensemble, nous avons lutté contre les vagues jusqu'à perdre connaissance d'épuisement.";
			link.l1 = "Vous avez été poussés contre l'un des navires ?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Oui, on s'est glissés dans un trou dans la cale... Là, j'ai perdu connaissance à nouveau, complètement épuisé. Je me suis réveillé quand Asana s'est mis à hurler — un crabe géant, monté sur la carcasse du navire, était en train de le déchiqueter. Et moi, paralysé par la peur et la faiblesse, je ne pouvais même pas bouger, tout en sachant que j'étais le prochain.";
			link.l1 = "Tu aurais pu essayer d'aider ton ami. Mais dans ce cas, on ne serait pas en train de parler, toi et moi. Comment as-tu fait pour t'en sortir ?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "T'as eu de la chance qu'il ait pas commencé par toi, "+npchar.name+". Comment tu t'es sauvé – t'as sauté à l'eau et t'es parti à la nage ?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Les cris d'Asana ont été entendus par plusieurs Rivadons, partis à la chasse au trésor dans les cales des navires après le dernier ouragan. Ils ont encerclé la bête et l'ont tuée. Pour Asana, il était déjà trop tard, mais moi, j'ai eu beaucoup plus de chance. C'est comme ça que je me suis retrouvé ici. Mais maintenant, c'est à toi de me répondre, mon ami : pourquoi voulais-tu savoir tout ça ?";
			link.l1 = "En fait, "+npchar.name+", je voulais savoir non pas comment tu t'es retrouvé ici, mais quand c'est arrivé.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Les cris d'Asana ont attiré plusieurs Rivares, partis fouiller les cales des navires après le passage d'un ouragan. Ils ont encerclé la créature et l'ont tuée. Pour Asana, il était trop tard, mais moi, j'ai eu beaucoup plus de chance. C'est comme ça que je suis arrivé ici. Mais maintenant, c'est à ton tour de répondre, mon ami — pourquoi voulais-tu connaître cette histoire ?";
			link.l1 = "En fait, "+npchar.name+", je voulais savoir non pas comment tu t'es retrouvé ici, mais quand c'est arrivé.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hmm, d'après votre calendrier, c'était l'année 1623, la fin de l'été – je ne peux pas être plus précis, ouais, hein...";
			link.l1 = "Ce n'est pas nécessaire. Donc, en 1638, cela faisait déjà quinze ans que tu étais sur l'Île.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "On dirait bien, mon ami.";
			link.l1 = "En juin de cette année-là, un ouragan a projeté contre l'anneau extérieur un brick nommé 'Wrangler', navire de la flotte de Sa Majesté Charles Ier, roi d'Angleterre. Seuls quatre membres de l'équipage ont survécu — dont les parents de Mary : Joshua et Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Ouais, je m'en souviens, mon ami. C'est flou, comme dans un brouillard, mais je m'en rappelle...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Tu t'en souviens, vraiment ? Raconte-moi, alors !";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Je ne peux en dire que peu de choses. Quatre personnes : un officier, sa femme et deux matelots. La femme était enceinte, et ceux qui les ont secourus pensaient qu'elle ne passerait pas la nuit — mais elle s'est révélée aussi forte qu'une lionne. Les deux marins, en revanche, ont quitté ce monde moins de vingt-quatre heures plus tard... Je les ai vus : ils étaient faibles, oui, mais ils avaient encore assez de force vitale...";
			link.l1 = "Tu insinues qu'ils ont été tués ?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "S'il en est ainsi, il n'y avait pas de témoins, pas plus que de blessures sur leurs corps, mon ami...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Tu as dit 'officier', ouais, hein... Mon père était vraiment officier ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Il portait un uniforme d'officier – c'est sans doute la seule chose dont je me souvienne quand j'essaie de me rappeler à quoi il ressemblait.";
			link.l1 = "S'il était officier, il ne pouvait rien porter d'autre – il est peu probable que sa garde-robe ait été très variée... Peut-être que tu te souviens d'autres détails, "+npchar.name+"? Des signes distinctifs... Disons, une cicatrice sur le visage ou une autre blessure...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Je ne me souviens de rien de particulier, mon ami. Son visage s'est presque effacé de ma mémoire – vingt ans ont passé… Mais son regard – ça, je m'en souviens très bien. Je n'ai parlé à cet homme qu'une seule fois, mais le regard de ses yeux gris – les mêmes que ceux de Mary – je ne l'oublierai jamais. Il y avait là un mélange de désespoir, de peur, comme une antilope traquée, et en même temps – une rage et une détermination dignes d'un lion…";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Tu lui as parlé, ouais, hein ? De quoi ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "C'est arrivé quelques heures avant ta naissance. Il est venu ici, sur le 'Protector', et a exigé de me rencontrer. Le chef des Rivares, Mogedi, était stupéfait par son audace — mais moi, cet homme a éveillé ma curiosité. Une fois devant moi, il est tombé à genoux et m'a supplié de sauver sa femme... Quelqu'un, durant leur court séjour ici, lui avait parlé de moi. J'ai accepté, bien que Mogedi s'y soit opposé...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Alors, je te dois la vie, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Inutile de mentir – nous avons réussi à rejoindre ta mère, mais trop tard : les narvals refusaient de me laisser monter à bord du 'Cérès Smitty'. Ton père a réussi à les... convaincre, mais la pauvre Thérèse, je ne l'ai vue qu'à son dernier souffle. Elle a eu le temps de te mettre au monde, et si j'étais arrivé plus tôt, peut-être que j'aurais pu lui sauver la vie, mais...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Maman est morte, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Hélas. Elle t'a regardé et a rendu son dernier souffle, mais avant cela, comme rassemblant ses forces, elle a appelé un certain Rupert. Elle a crié son nom de toutes ses forces, comme si elle appelait à l'aide – puis elle est morte.";
			link.l1 = "Ruperta ? Pas Joshua ?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Pendant que je te racontais cela, mon ami, c'était comme si je revivais ce moment. Je ne l'oublierai jamais — ni son cri d'agonie, ni son visage déformé par la souffrance. Et oui, le dernier mot qui a franchi ses lèvres, c'était bien 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Elle était belle, ma mère ? Tu peux me décrire à quoi elle ressemblait, Chimiset ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "Ça n'a aucun sens, Mary. Il te suffit de te regarder dans un miroir – vous vous ressemblez comme deux gouttes d'eau. Seul ce regard perçant te vient de ton père.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "Et lui, qu'est-ce qu'il est devenu ? On a réussi à apprendre que quelques jours après ma naissance, il s'est comme volatilisé, ouais, hein ? Mais il n'a pas été tué, pas vrai ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Dès qu'il a appris que Teresa était mourante, Joshua est entré dans une rage folle — je te jure, même les lions de la savane n'attaquent pas leur proie avec autant de fureur que ton père en a montré contre ces Narvals qui m'empêchaient de monter sur le flûte... Il a fallu une demi-douzaine d'hommes pour le maîtriser — après qu'il eut balancé à l'eau deux guerriers du clan en tenue complète.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "Et qu'est-ce que vous lui avez fait – dis-moi, allez !";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "On l'a enfermé dans l'une des cellules du 'Tartarus'. Personne n'a osé le juger — on voulait d'abord que cette affaire se tasse... Presque tout le monde le plaignait, mais peu souhaitaient vivre aux côtés d'un homme comme lui. Joshua a disparu quelques jours plus tard — à ce moment-là, plusieurs barcasses de contrebandiers ont quitté l'Île. Personne ne l'a vu dans les embarcations — c'est ce qui a fait naître les rumeurs sur sa mort.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Alors, tu crois qu'il est vivant, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Je dirai seulement ce que d'autres ne manqueront pas de vous dire aussi : on n'a jamais retrouvé son corps. Peut-être qu'il s'est caché au fond d'une barque, ou alors on lui a tranché la gorge dans cette cellule et on a donné son cadavre aux crabes...";
			link.l1 = "Le fait qu'il ait disparu en même temps que le départ de ces trafiquants plaide plutôt pour la première option — ce genre de coïncidence n'existe pas. Et peut-être qu'il a laissé échapper quelque chose sur ses projets ? S'il s'est enfui, il l'a fait en laissant ici sa fille nouveau-née — ce qui, d'un certain point de vue, est plutôt sensé : un nourrisson n'aurait sans doute pas survécu à une traversée vers Cuba dans une barcasse… Mais il comptait sûrement revenir la chercher.";
			link.l1.go = "WildRose_Chimiset_51";
		break;

		case "WildRose_Chimiset_51":
			dialog.text = "Je l'ignore, mon ami. Si Joshua Casper a parlé à quelqu'un dans ces jours-là, ce ne pouvait être qu'aux gardiens — mais tous ont depuis longtemps quitté ce monde pécheur. Ah, oui, un jour, le padre Domingo est allé le voir — c'était le prêtre des Blancs avant frère Julian...";
			link.l1 = "Il voulait se confesser, ou quoi ? On dirait qu'il avait peur de mourir en s'évadant.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Je ne peux pas éclairer ce que j'ignore, mon ami. Et Domingo non plus ne vous racontera plus rien – il s'est noyé il y a bien quinze ans. On ne sait pas si on lui a fendu le crâne ou s'il était juste saoul – il aimait bien ça, lui…";
			link.l1 = "Mais peut-être que Domingo tenait un journal... ou qu'il a raconté cette conversation avec Joshua à son frère Julian ?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Il faut lui parler, "+pchar.name+", ouais. Et le plus vite possible. Je ne veux même pas penser à retourner sur le navire tant qu'on n'a pas réglé ça.";
			link.l1 = "S'il y a encore des choses à éclaircir. Julian n'est peut-être même pas au courant – mais on va le découvrir, c'est sûr. Merci à toi, Chimisette.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Je suis toujours à ton service, mon ami. Mais permets-moi de vous donner à tous les deux un conseil.";
			link.l1 = "Et lequel ?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Quand vous partez chasser, ne vous enfoncez pas trop loin dans les broussailles – vous pourriez bien ne jamais en ressortir.";
			link.l1 = "On s'en souviendra, chaman. Et maintenant – adieu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Je vous salue sous l'abri de la maison de Dieu, mes enfants. Vous venez vous confesser ou simplement prier ?";
			link.l1 = "Bonjour, frère Julien. J'ai bien peur que l'énumération de nos péchés prenne trop de temps – temps que, hélas, nous n'avons pas. Mais soyez assuré : en bons catholiques, nous allons à l'église dans chaque port.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Bienvenue, frère Julien. Par la prière à notre Seigneur, nous, bons catholiques, commençons la journée et la terminons de même.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "De bons catholiques qui vivent sous le même toit sans être mariés... C'est presque un blasphème, mon fils. Et je te rappelle que c'est un péché mortel !";
			link.l1 = "Et n'est-il pas écrit dans les Écritures que l'amour couvre tous les péchés ?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "De bons catholiques qui vivent sous le même toit sans être mariés... C'est presque un blasphème, mon fils. Et je te rappelle que c'est un péché mortel !";
			link.l1 = "Et n'est-il pas écrit dans les Écritures que l'amour couvre tous les péchés ?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "L'amour consiste à suivre Ses commandements — dois-je te les rappeler, mon fils ?";
			link.l1 = "Une autre fois, peut-être. On est ici pour autre chose.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Il n'est jamais trop tard pour les âmes égarées de retrouver le droit chemin... Mais je vous écoute, mes enfants.";
			link.l1 = "Nous nous sommes vraiment un peu perdus, frère Julian. Dans les méandres du passé. Et nous espérons que vous pourrez nous aider à retrouver le chemin vers la lumière.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Très spirituel, mon fils. Tu dois te rappeler que ce n'est pas l'homme qui mène à la lumière, mais le Seigneur – et, en Le suivant, souviens-toi que Ses voies sont impénétrables.";
			link.l1 = "Je vais faire court, frère Julian. Nous essayons de découvrir tout ce que nous pouvons sur les parents de Mary. Pour sa mère, Teresa, c'est à peu près clair — elle est arrivée sur l'Île avec son mari et est morte en couches une semaine plus tard. Mais le père… Il a disparu quelques jours après la naissance de Mary, en s'évadant du 'Tartarus'. D'après les rumeurs, le dernier à lui avoir parlé ici serait le padre Domingo — votre prédécesseur.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Alors là, vous arrivez avec plus d'une quinzaine d'années de retard, mes enfants.";
			link.l1 = "Ouais, on sait que le padre est mort il y a déjà pas mal de temps. Et à cette époque-là, frère Julian, t'étais encore trop jeune pour être sur l'Île avec le rang approprié, pas vrai ?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Je me suis retrouvé ici quelques années après sa mort. Il m'a fallu beaucoup d'efforts pour remettre de l'ordre ici, sur ce navire, mais avec l'aide de Dieu, j'y suis arrivé, mon fils.";
			link.l1 = "En fouillant ici, vous n'auriez pas trouvé des écrits du padre Domingo ?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Avez-vous quelque chose de précis en tête, mon fils ?";
			link.l1 = "Nous cherchons des journaux ou des registres... On n'a pas beaucoup d'espoir, mais le padre a peut-être noté le contenu de cette conversation quelque part. On suppose que le père de Mary a quitté l'île à bord d'une des barques des contrebandiers – peut-être a-t-il laissé entendre au padre où il comptait aller et quand il reviendrait chercher sa fille ?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Je n'ai certainement trouvé aucun journal ou quoi que ce soit de ce genre, mais en revanche, toutes sortes de registres... En matière d'affaires ecclésiastiques, il faisait preuve d'une grande rigueur — le Seigneur ne donne pas à chacun de Ses serviteurs un tel sens du détail. Mais ses papiers ne contiennent que des chiffres secs et des noms — rien de plus.";
			link.l1 = "Autant que nous avons pu l'apprendre, Joshua Casper — c'était bien son nom — dans un accès de rage provoqué par la mort de sa femme, a tué deux membres du clan 'Narval' qui avaient refusé de laisser entrer le sorcier rivados Chimisetu auprès de la mère de Mary...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Ils ont agi comme de vrais enfants de la Sainte Église ! Les cachots de l'Inquisition n'attendent que ce serviteur du Diable !";
			link.l1 = "Je pense que le Seigneur serait horrifié — s'Il savait combien de gens ont été torturés en Son nom. Casper a eu plus de chance — on l'a enfermé dans une cellule du 'Tartarus', mais il n'y a jamais eu de procès.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Ouais, ouais, sans aucun doute. Casper a été jeté dans l'une des cellules du 'Tartarus', mais il n'y a pas eu de sentence – tout le monde n'a pas condamné l'acte d'un mari ayant perdu sa femme.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "Et ensuite ? Cet hérétique s'est enfui ?";
			link.l1 = "Moins d'une semaine plus tard, Joshua a disparu. Et la nuit précédente, il a reçu la visite du padre Domingo. La question se pose : pourquoi ? Il est peu probable qu'un protestant, ce que Casper était sûrement, aille se confesser à un prêtre catholique — qu'en pensez-vous ?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "Et après, ce hérétique s'est enfui ?";
			link.l1 = "Moins d'une semaine plus tard, Joshua a disparu. Et la veille au soir, il a reçu la visite du padre Domingo. La question se pose : pourquoi ? Il est peu probable qu'un protestant, ce que Casper était sûrement, soit allé se confesser à un prêtre catholique – qu'en pensez-vous ?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Il n'est jamais trop tard pour se tourner vers la vraie foi, mon fils. Mais tu raisonnes bien. S'il n'était pas venu pour une confession, alors peut-être discutait-il avec le padre de l'enterrement de sa femme — si toutefois elle était catholique. Ou bien du baptême de sa fille, ou plutôt de son refus, puisque les protestants ne baptisent pas les nourrissons, estimant que chacun doit prendre une décision consciente et personnelle à ce sujet.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Mais j'ai été baptisée, frère Julian. Erik Udett m'en a parlé.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Ce ne sont que mes suppositions, ma fille. La vérité m'est inconnue. Le Seigneur ne nous ouvre les yeux que sur ce qui est vraiment important et nécessaire.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "Et pour moi, c'est bien le cas, ouais, hein ? Peut-être qu'il reste encore quelque chose dans les pages des notes du padre Domingo que vous n'avez pas remarqué, frère Julian ? Après tout, vous ne faisiez que les feuilleter, n'est-ce pas ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "Je n'avais rien à y chercher, ma fille. Je vois que vous vous occupez de cette affaire depuis longtemps et avec soin – le Seigneur vous guide sur ce chemin semé d'embûches. Si tu es destinée à trouver ce que tu cherches, telle est Sa volonté, et il ne m'appartient pas de m'y opposer. Je peux vous donner les registres de Domingo pour l'année de ta naissance, peut-être y trouverez-vous quelque chose d'utile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Ce serait très généreux de votre part, frère Julien. Est-ce qu'il reste des registres pour l'année 1638 ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Voyons voir... (elle souffle la poussière). Il me semble que c'est ça. Le registre comptable de l'an 1638 après la naissance du Christ.";
			link.l1 = "Laisse-moi faire, frère Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Regarde, "+pchar.name+": Le 3 août. Ce jour-là, on m'a baptisée, moi et Fabian. Mais je suis née le 22 juin. Par contre, pas un mot sur mon père, ouais, hein ?";
			link.l1 = "Tout est exactement comme l'a dit frère Julian : des chiffres secs et des noms. Ce qui est intéressant, c'est que le padre Domingo était tellement zélé qu'il a même donné l'extrême-onction aux protestants – difficile de croire que van Ekkus, Young et Friddicks étaient catholiques.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Ils ont très bien pu se tourner vers la vraie foi à l'instant d'entrer dans le Royaume de Dieu, mon fils.";
			link.l1 = "Bien sûr, frère Julian – qu'auraient-ils pu faire d'autre ? Surtout s'ils sont morts comme Sorrens et Rojas – je suppose que ce sont ces narvals-là qui ont barré la route à Chimiset.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Il aurait mieux valu que le padre Domingo écrive les deuxièmes prénoms en entier, ouais, hein ? Qu'est-ce que ça veut dire, ces 'V.' et 'Dj.' après les prénoms de ma mère et moi ?";
			link.l1 = "Et qui est ce Fabian, celui qui a été baptisé le même jour que toi ?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Le fils de Cécile Gallard. Oh, je viens juste de m'en souvenir ! C'est elle qui m'a élevée, même si elle n'a jamais été très chaleureuse avec moi. Sûrement parce que moi, j'ai survécu, et pas Fabien. Il est mort quelques mois après sa naissance, ouais, hein ?";
			link.l1 = "Peut-être qu'on devrait lui parler, vu que ce bouquin ne nous a presque rien appris d'utile – à part, bien sûr, les dates de ta naissance et de ton baptême.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Elle n'est pas beaucoup plus jeune qu'Aurélie, "+pchar.name+". Il ne reste plus qu'à espérer qu'au moins elle, elle a toute sa tête. Mais qu'est-ce que tu comptes lui demander ?";
			link.l1 = "Eh bien, puisqu'elle était ta nourrice — elle a peut-être appris quelques détails de la conversation entre le padre Domingo et Joshua. À qui d'autre aurait-il pu les raconter, sinon à elle ? Peut-être aussi à Aurélie ou à Eric. Mais j'ai l'impression que nous avons déjà tiré tout ce que nous pouvions d'Aurélie, et qu'Eric ne dira plus rien à personne.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Cette brave femme est une fidèle paroissienne de cette maison de Dieu. Elle ne manque jamais une messe et se confesse régulièrement. Je pense qu'elle peut vraiment vous aider, mes enfants.";
			link.l1 = "Merci à vous, père. Adieu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" et Mary Casper. Quelle rencontre agréable !";
			link.l1 = "Rav"+GetSexPhrase("e","i")+" de te rencontrer, "+npchar.name+". En fait, c'est à vous que nous venons. Nous aimerions discuter de quelque chose avec vous.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Ah bon ? Eh bien, je t'écoute.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Il s'agit de mes parents, Cécile. Pour ma mère, on a déjà découvert tout ce qu'on pouvait… Elle est morte juste après ma naissance. Mais mon père… il a disparu sans laisser de trace quelques jours plus tard. On pense plutôt qu'il n'est pas mort, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "Eh bien, pour envoyer un homme comme lui dans l'autre monde, il fallait vraiment s'y prendre...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Tu l'as vu ? Tu lui as parlé ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Ma petite, je l'ai vu s'occuper de deux narvals presque à mains nues...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = " Avec Sorrento et Rojas ? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "Déjà à l'époque, j'avais bien assez à faire pour retenir les noms de ces vauriens – alors maintenant, je ne m'en souviens plus du tout.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "D'accord, ce n'est pas important. Continue, s'il te plaît, Cécile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "Et alors, qu'est-ce qu'il y a à raconter ? Il a balancé ces deux-là à l'eau, ils ont coulé comme des pierres, et lui, on l'a maîtrisé et emmené sur le 'Tartarus’. Et ils ont bien fait — qui sait encore qui ce bandit aurait voulu noyer…";
			link.l1 = "Un tueur ? C'est un peu rude, vous ne trouvez pas, madame Gallard ? On parle d'un homme, d'un officier, qui vient tout juste de perdre sa femme...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Je vois que vous n'avez pas la meilleure opinion de lui – on ne dirait pas ça de n'importe quel officier.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Officier, vraiment ? Son uniforme, ça oui, il était impeccable — je m'en souviens encore. Presque comme neuf. Mais j'en ai vu beaucoup, des officiers, jeune homme. Et tous se comportaient bien plus dignement que ce... monsieur.";
			link.l1 = "Il a fait autre chose ? À part tuer ces deux-là ?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Officier, eh bien, eh bien. Son uniforme était vraiment élégant, je m'en souviens comme si c'était hier. Presque flambant neuf. Mais j'en ai vu, des officiers, jeune homme. Et tous se comportaient bien plus dignement que ce... monsieur.";
			link.l1 = "Il a fait autre chose ? À part tuer ces deux-là ?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Il a demandé qu'on fasse venir un prêtre dans sa cellule – le padre De la Cruz...";
			link.l1 = "Eh bien, ça alors ! C'est justement de ça qu'on voulait vous parler. Vous connaissez les détails de cette conversation ?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Eh bien sûr, jeune homme ! Ce vaurien de protestant a exigé du padre qu'il ne baptise pas sa fille – alors même que sa mère était irlandaise, donc catholique.";
			link.l1 = "C'est bien la première fois que j'entends une Anglaise parler ainsi d'un protestant... Hum, pardon de vous avoir interrompue, madame "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "J'ai été protestante moi aussi, faut bien l'avouer. Mais frère Julian a réussi à me remettre dans le droit chemin.";
			link.l1 = "Vraiment... Un serviteur du Seigneur des plus compétents. Mais nous nous égarons. Donc, Casper voulait que sa fille soit élevée dans la foi protestante.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "C'est exactement ce qu'il a dit à notre padre De la Cruz. Et puis, il a aussi ordonné d'appeler la petite Julia...";
			link.l1 = "Alors c'est ça, ce que veut dire ce 'J.’. Mary Julia Casper… Mais pourquoi alors l'ont-ils appelée Mary ?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Parce que c'est ce que voulait sa mère, voilà pourquoi. Quand on a sorti la petite de son ventre, elle a murmuré un nom – Mary. J'en ai pas été témoin, mais Aurélie Bertin était là pendant l'accouchement. Vous pouvez lui demander, si vous voulez...";
			link.l1 = "Donc, c'est le souhait de la mère qui a été pris en compte.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "Et comment ça aurait pu être autrement – vu que ce pauvre père s'est littéralement volatilisé ?";
			link.l1 = "Vu... les talents du padre De la Cruz, je doute que l'avis de son père aurait compté, même s'il était resté tranquillement à bord du 'Tartarus’. Domingo ne vous en a rien dit — il n'était pas au courant des projets de Casper concernant l'évasion et un possible retour pour la gamine ?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Vous avez sans doute raison. Mais pour en revenir à la conversation entre le padre Domingo et monsieur Casper — le prêtre n'a-t-il pas mentionné que Joshua aurait peut-être parlé de sa fuite et d'un éventuel retour pour récupérer sa fille ?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "Il ne m'a jamais rien raconté de tel. Et puis, réfléchis toi-même, ouais, hein ? "+npchar.name+",   si vous prépariez une évasion de prison, est-ce que vous en parleriez au premier venu ? Ce type-là, il ne l'aurait sûrement pas fait, je vous le dis.";
			link.l1 = "Donc, ce fil nous a menés nulle part. Eh bien, merci de nous avoir accordé votre temps, madame "+npchar.lastname+". On se reverra.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "Il n'a jamais parlé de rien de tel. Et puis, réfléchis toi-même, ouais, hein ? "+pchar.name+",   si vous comptiez vous évader de prison, est-ce que vous en parleriez au premier venu ? Ce type-là, il ne l'aurait sûrement pas fait, moi je vous le dis.";
			link.l1 = "Donc, ce fil nous a menés nulle part, hein ? Eh bien, merci de nous avoir accordé de votre temps, madame "+npchar.lastname+". On se reverra.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "On a découvert pas mal de choses intéressantes, "+pchar.name+". Mais on n'a pratiquement pas avancé, ouais, hein ?";
			link.l1 = "Et même un peu embrouillés. Qui donc est ce Rupert, à qui ta mère a appelé avant de mourir ?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Peut-être un frère ou... un ami proche ?";
			link.l1 = "Ami, tu dis, eh bien... Je me demande si Joshua était au courant de lui...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "Qu'est-ce que tu insinues, "+pchar.name+"?";
			link.l1 = "Que tout cela mérite une bonne réflexion. Heureusement, on aura tout le temps d'y penser pendant qu'on cherchera quelqu'un pour nous aider dans nos recherches. On a déjà fait un sacré bout de chemin. Mais on n'est pas encore au bout. Nous, on n'a aucun accès à la chancellerie de la Royal Navy — et elle se trouve de l'autre côté de l'océan, à Londres... Tu aurais une idée de qui pourrait nous filer un coup de main là-dessus ?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "Et Sarge Benoît, Charles ?";
			link.l1 = "L'abbé ? Il a de grandes relations, c'est vrai, mais accéder aux archives de la Marine Royale, il n'y arrivera sans doute pas.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = " S'il ne peut pas lui-même, il pourra peut-être nous présenter à quelqu'un qui en est capable, ouais, hein ? ";
			link.l1 = "On dirait bien. Cap sur Saint-Pierre, alors.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. 'БУМАЖНАЯ РАБОТА' ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Eh bien, maintenant il ne nous reste plus qu'à attendre, ouais, hein ?";
			link.l1 = "Je suis sûr qu'il va tout découvrir, "+npchar.name+" . Le temps passera vite, tu ne t'en rendras même pas compte. En attendant, on a de quoi s'occuper.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Tu fais allusion à quelque chose en particulier, mon amour ?";
			link.l1 = "On a plein de choses à faire, mais pourquoi on ne retournerait pas sur le navire maintenant, on fermerait la porte et on passerait un peu de temps rien que tous les deux ? Qu'est-ce que t'en dis ?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "Je savais que tu allais proposer ça, ouais, hein ! Écoute-moi bien : ne perdons pas de temps !";
			link.l1 = "Viens, ma belle adorée.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", tu n'imagines pas, vraiment tu n'imagines pas, quel poids vient de tomber de mon âme, ouais, hein !";
			link.l1 = "Très bien, ma chère – tu rayonnes littéralement, haha ! Comme tu vois, tout cela en valait la peine.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Mon père était un officier renommé, tu te rends compte ! Mais c'est tellement triste, on n'a jamais eu la chance de se rencontrer. Et on ne saura jamais s'il a réussi à rejoindre le continent, ouais, hein…";
			link.l1 = "S'il était arrivé quelque chose, il serait sûrement retourné au service, et on aurait entendu parler de lui quelque part, non ? Un homme comme lui n'aurait jamais pu rester en place tranquillement – sinon, de qui tu tiendrais ça, hein ?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Tu penses vraiment qu'il est mort ? Qu'il est tombé entre les mains des Espagnols à Cuba, ou qu'il a carrément été tué sur l'Île de la Justice ?";
			link.l1 = "J'essaie de regarder la vérité en face, ouais, hein ? "+npchar.name+". À cette époque, il y avait tout de même une certaine liaison avec l'Île, les contrebandiers y allaient régulièrement sur leurs tartanes. S'il avait pu quitter l'Île, je n'en doute pas, il y serait revenu te chercher quelque temps plus tard.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Pour venir me chercher là-bas. Mais alors on ne se serait jamais rencontrés, ouais, hein ?";
			link.l1 = "C'est la vie, ma chère. On ne sait jamais où l'on trouve, ni où l'on perd. J'espère que tu ne regrettes pas d'être ici avec moi, maintenant.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Jamais entendu une plus grande bêtise de ma vie, ouais, hein ! "+pchar.name+", t'es le meilleur, t'es vraiment génial ! Merci d'avoir fait tant d'efforts pour m'aider à tout découvrir. C'est tellement important pour moi, ouais, hein ! Mais viens, on va étudier les documents – peut-être qu'on y trouvera quelque chose que notre ami ne nous a pas dit…";
			link.l1 = "Bonne idée. On commence tout de suite.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Eh bien, "+pchar.name+", tu as remarqué quelque chose d'intéressant ? ";
			link.l1 = "Ouais, "+npchar.name+". J'ai quelque chose... ";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "On dirait que t'as vu un fantôme, ouais, hein ?";
			link.l1 = "Il est question ici d'un certain Rupert Northwood.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood ?! Vraiment – le fameux ?";
			link.l1 = "Chut, "+npchar.name+" - Ne crie pas comme ça. Hm... Je pense que ouais, hein, c'est bien la personne dont parlait Chimiset. Ça ne peut pas être autrement – des coïncidences pareilles, ça n'existe pas.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "Et qu'est-ce que tu en penses, ouais, hein ? "+pchar.name+"?";
			link.l1 = "Cette histoire devient de plus en plus embrouillée. Donc... le 'Cornwall' est parti de Plymouth, c'est aussi le 'Cornwall' qui est arrivé à Antigua, mais c'est le 'Wrangler' qui s'est écrasé sur les récifs de l'Île de la Justice — toujours avec Joshua Casper à son bord, lequel avait réussi à épouser en secret, à l'insu de l'Amirauté, une femme qui, en mourant, appelait un certain Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Je ne comprends rien. Je ne sais même pas qui pourrait encore nous éclairer un peu là-dessus. Plus on essaie d'en savoir sur mon père, plus on s'enfonce dans un marécage de mystères et de secrets toujours nouveaux, ouais, hein ?";
			link.l1 = "S'il y a bien quelqu'un qui peut encore éclaircir quoi que ce soit, c'est soit Joshua Casper, soit Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood ? Mais il est mort, ouais, hein ? Tu ne penses quand même pas que le rapport rédigé à l'arrivée du 'Cornwall' à Saint John contient de fausses informations ?";
			link.l1 = "Ah, cette naïveté qui te colle à la peau, "+npchar.name+"... Je commence à penser que toute cette histoire est complètement imprégnée de mensonges. Réfléchis : Joshua Casper était un officier exemplaire — décoré à maintes reprises, sans la moindre sanction. C'est difficile à concilier avec ce qu'on a appris sur lui à l'Île de la Justice, où il a envoyé deux hommes ad patres sans la moindre hésitation, tu ne trouves pas ?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Il s'est battu pour la vie de sa femme, ma mère, "+pchar.name+"!";
			link.l1 = "Sans aucun doute, mais réfléchissons, d'où cela vient-il au juste ? Et surtout, pourquoi a-t-il caché son mariage à l'Amirauté ? Un soldat jusqu'au bout des ongles, un officier fidèle au règlement et à son devoir – sinon son dossier ne serait pas aussi irréprochable – et soudain, un tel écart.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "Et si derrière tout ça se cachait une belle histoire romantique ? Ça arrive, même si c'est rare, ouais, hein ?";
			link.l1 = "Ne te méprends pas, Mary, mais tout ça ne ressemble pas à une histoire romantique. Plutôt à une sorte de mise en scène, dont le but reste flou. Pourquoi renommer un navire en route vers Providence ? C'est un bâtiment militaire — ce genre de fantaisie peut valoir une cour martiale.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "D'accord – bonne question.";
			link.l1 = "Et puis, il y a clairement quelque chose de louche avec ce Rupert Northwood. Presque la moitié de l'équipage est tombée au combat, mais, chose étrange, pas un seul officier, à part lui. Et pourquoi ta mère, avant de mourir, a-t-elle appelé Rupert, et non son mari Joshua ?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Donc, tu es vraiment sûr que le second n'est pas mort au combat contre les Espagnols, hein ? Et que je ne suis pas la fille de Joshua Casper, mais de Rupert Northwood – c'est là où tu veux en venir ?";
			link.l1 = "Comme je l'ai déjà dit — une seule personne connaît la vérité. Soit Joshua Casper, qui a appelé Teresa sa femme pour une raison inconnue, soit Rupert Northwood, qui, pour des motifs tout aussi obscurs, a pris le nom de son capitaine.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Eh ben, quel sacré bazar, ouais, hein ! Et qu'est-ce qu'on va faire maintenant, "+pchar.name+" ? Maintenant j'ai encore plus envie de découvrir la vérité, mais on a déjà tiré tout ce qu'on pouvait de tout le monde.";
			link.l1 = "S'il y a un endroit où trouver des réponses, c'est bien sur l'Île de la Justice – il ne reste plus personne ailleurs, sauf peut-être de l'autre côté de l'océan, qui ait connu tes parents, même brièvement. Je pense qu'il vaudrait la peine de reparler à Aurélie Bertin – peut-être qu'elle se souviendra encore de quelque chose à quoi on pourrait se raccrocher.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Mais qu'est-ce que tu veux lui demander de plus ? Il me semble qu'elle nous a déjà tout dit, non ?";
			link.l1 = "Elle a parlé de ce qu'on lui a demandé, et elle a très bien pu oublier un détail important. Peut-être que ton père avait une cicatrice sur le visage, ou qu'il lui manquait un doigt à la main… J'ai du mal à croire qu'un homme capable d'inventer tous ces tours avec le changement de nom du navire, et peut-être même de son propre nom, ait pu disparaître misérablement sur une île ou dans les cachots des Castillans.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Tu as sans doute raison...";
			link.l1 = "Et si nous décidons de poursuivre nos recherches – non plus sur les étagères poussiéreuses de l'Amirauté, mais ici, dans l'Archipel, il nous faudra quelque chose de plus qu'un simple nom, et en plus un faux, ouais, hein ?";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Tu sais, tout ça me donne la chair de poule, ouais, hein ? Je ne sais pas si c'est parce que tout ça est… grisant, ou parce que je me dis que mon père n'était peut-être pas si différent de ce salaud de la plantation Bishop.";
			link.l1 = "Quoi qu'il en soit, je te promets qu'on fera tout notre possible pour comprendre ce qui se passe. Alors, ne perdons pas de temps. En route !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. 'ПУТЬ К СВЕТУ' =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Allons-y, "+pchar.name+", ne perdons pas notre temps pour rien, ouais, hein ?";
			link.l1 = "J'espère qu'Aurélie est dans sa cabine, et qu'on n'aura pas à fouiller toute l'Île à sa recherche...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "On dirait qu'on n'a encore pas eu de chance, ouais, hein ? Mais où est-ce qu'elle a bien pu passer ?";
			link.l1 = "J'espère que la maladie n'a pas de nouveau pris le dessus sur son esprit...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, vous êtes de retour. Eh bien, bonjour... Qu'y a-t-il, vous avez encore besoin d'Aurélie ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "On ne peut pas te reprocher de manquer de jugeote, Gillian. Tu ne saurais pas, par hasard, où elle est ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "À l'église, elle allait se confesser. Si vous vous dépêchez, vous la trouverez là-bas.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Eh bien, si elle se confesse, c'est qu'elle est sûrement saine d'esprit et parfaitement lucide, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Il est difficile à dire... Ces trois derniers jours, elle n'est plus elle-même, elle ne tient pas en place. Vous savez, elle s'est mise dans un drôle d'état en voyant les mâts de votre navire derrière l'anneau extérieur.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Je me demande bien pourquoi, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Elle doit sans doute détester l'idée d'être à nouveau interrogée par toi. Mais depuis quand les problèmes des autres t'ont-ils jamais préoccupé, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Ne me parle pas sur ce ton, Gillian. Je te pardonne cette fois, mais essaie encore une fois de dire quelque chose comme ça...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Quelle personne nerveuse, dès que ça ne va pas comme elle veut, hein ?";
			link.l1 = "Inutile de la provoquer sans raison, "+npchar.name+". Vous savez bien qu'elle ne porte pas son épée pour faire joli.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "Et vous auriez laissé une chose pareille arriver, "+pchar.name+"?";
			link.l1 = "Vous n'avez tout simplement pas vu Mary au combat, "+npchar.name+". Sinon, ils ne se berceraient pas d'illusions en pensant que quelqu'un ou quelque chose pourrait l'arrêter.   On se reverra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Tu veux sûrement me demander quelque chose, ouais, hein ? "+pchar.name+", ouais...";
			link.l1 = "Pour être honnête, je me fiche un peu de quel chat noir est passé entre vous, même si j'ai une idée de son nom. Ou plutôt, de son ancien nom. Tu tiens vraiment à en parler ?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Toi et Gillian, vous vous êtes disputées pour quelque chose ? Ou plutôt, pour quelqu'un ?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hmm, en fait, non.";
			link.l1 = "Comme tu veux. Et maintenant, allons chercher Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Cette fouine ne me pardonnera jamais qu'Alan m'ait préférée à elle. Pourtant, elle pourrait bien — vu qu'il n'est plus là… À vrai dire, "+pchar.name+", je préférerais ne pas en parler, ouais, hein.";
			link.l1 = "Comme tu veux, ma belle. Alors, on va chercher Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary ! Vous êtes de retour sur l'Île, quelle joie !";
			link.l1 = "Ravis de voir que vous êtes en bonne santé, "+npchar.name+". En fait, nous sommes venus sur l'Île pour vous reparler. Mais ne vous inquiétez pas, ça ne prendra pas beaucoup de temps.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Oh là là, les jeunes, vous n'avez vraiment aucune pitié pour une vieille dame. Mais je sentais que vous viendriez. C'est encore à propos de tes parents, ouais, Mary ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "S'il te plaît, Aurélie. Je comprends que c'est difficile pour toi de t'en souvenir après tout ce temps, mais essaie encore une fois, d'accord, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Je vous ai déjà tout raconté, tout ce dont je me souviens. Je ne comprends vraiment pas ce que vous voulez encore me soutirer.";
			link.l1 = "On va vous poser quelques questions, "+npchar.name+". Essayez, s'il vous plaît, de vous souvenir de quelque chose – des détails ou des précisions. Nous n'allons pas vous mettre la pression...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "Mais n'est-ce pas exactement ce que vous êtes en train de faire en ce moment ?";
			link.l1 = "Vous avez déjà fait tant pour nous, "+npchar.name+"... Nous espérons simplement que dans les labyrinthes de votre mémoire, il se trouvera encore quelque chose qui pourra beaucoup nous aider.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "On a fait un long chemin, "+npchar.name+". Vous n'imaginez même pas combien d'efforts et de temps il nous a coûté. Mais nous nous sommes égarés, et il n'y a que vous et votre mémoire pour nous remettre sur le chemin de la vérité.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "De la mémoire... Qu'est-ce qu'il en reste, de cette mémoire. Parfois, le matin, je n'arrive même pas à me rappeler comment je m'appelle, et vous, vous voulez que je me souvienne des détails — d'événements d'il y a vingt ans. Mais soit, allez-y, demandez.";
			link.l1 = "Nous nous intéressons à Monsieur Casper, le père de Mary. Vous pouvez vous rappeler quelque chose de particulier dans son apparence ? Peut-être avait-il une cicatrice sur le visage, ou il boitait beaucoup...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "De la mémoire... Qu'est-ce qu'il en reste, de cette mémoire-là. Parfois, le matin, je ne me rappelle même plus comment rejoindre la cambuse, et vous voudriez que je me souvienne des détails — de ce qui s'est passé sur ces épaves il y a vingt ans. Mais bon, soit, allez-y, posez vos questions.";
			link.l1 = "Nous nous intéressons à Monsieur Casper, le père de Mary. Vous souvenez-vous de quelque chose de particulier dans son apparence ? Peut-être avait-il une cicatrice sur le visage, ou il boitait beaucoup...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Oh là là... Il me semble que j'ai déjà mentionné que je ne l'ai vu que dans l'obscurité totale, dans la cale du 'Cérès Smithy’, là où ils avaient installé une couchette pour la pauvre Thérèse. Il ne boitait absolument pas – au contraire, c'était un homme plutôt vif.";
			link.l1 = "Et son âge ? Il était jeune ou déjà âgé ?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Je ne l'aurais pas vraiment appelé un vieillard… Mais je ne faisais pas trop attention à lui – c'est plutôt Teresa qui m'inquiétait. Il avait l'air mal en point, c'est vrai – on aurait dit un fantôme. Mais il faut dire que toute la semaine où sa femme était sur le point d'accoucher, il n'a presque pas dormi… Il courait partout sur l'Île, sans s'arrêter.";
			link.l1 = "Il aimait donc beaucoup sa femme. Et vous, vous passiez beaucoup de temps avec elle, non ? Elle ne parlait jamais de son mari ?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Thérèse demandait sans cesse après lui. Elle dormait beaucoup, parfois elle délirait, mais dès qu'elle reprenait ses esprits, elle demandait tout de suite où il était. Et la pauvre, elle l'attendait avec tant d'impatience. Mais au moment le plus important – il n'est jamais venu.";
			link.l1 = "Je vois. De toute évidence, leur amour était réciproque... Eh bien, merci, Aurélie. Vous nous avez vraiment beaucoup aidés.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "Et c'est tout ? Je croyais qu'on allait discuter pendant des heures, ouais, hein ?";
			link.l1 = "On avait promis de ne pas vous tourmenter trop longtemps. Prenez soin de vous, "+npchar.name+". Prends soin de toi.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Attendez, les jeunes gens ! J'ai encore quelque chose pour vous… Enfin, plutôt pour toi, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Tiens, ma fille, prends... Dès que j’ai vu les voiles de votre navire, j’ai pris ce chapeau avec moi pour ne pas l’oublier. Mais descendre jusqu’au quai... je n’ai pas osé.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Qu'est-ce que c'est, Aurélie ? Un chapeau ?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Le chapeau de ta mère, Thérèse. Elle l'avait avec elle quand les survivants du naufrage ont été amenés sur le 'Cérès Smitty'. Quand Thérèse est morte, j'ai ramassé ce chapeau par terre, près de son lit – puis je l'ai oublié… Je ne m'en suis souvenue qu'aujourd'hui, pendant notre conversation.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = " Aurélie... Tu l'as gardée toutes ces années ! Et... et tu ne l'as ni jetée, ni vendue... Merci, merci à toi ! Tu n'imagines même pas à quel point c'est... précieux et important pour moi, ouais, hein !";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Pardon, Mary – j'aurais dû te la rendre depuis belle lurette… Mais ma mémoire, c'est un vieux tamis percé, tu vois… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "On ne pouvait pas rêver meilleur moment, Aurélie ! Je vais l'essayer tout de suite, ouais, hein ?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Alors, mon cher, comment tu me trouves?..";
			link.l1 = "Tu es magnifique. Et puis, le chapeau... il n'est pas encore passé de mode, alors il te va très bien aussi, ouais, hein ?";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Vraiment ? Je suis tellement contente que ça te plaise, ouais, hein !";
			link.l1 = "Et comment ça pourrait être autrement ?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Merci encore, Aurélie — vous avez rendu cette journée un peu plus lumineuse ! Prenez soin de vous et reposez-vous bien.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Alors, c'était donc bien Rupert. Rupert Northwood, ouais, hein.";
			link.l1 = "Évidemment que oui, ma chère. Il a tout fait pour sauver sa femme... ou sa bien-aimée, je ne sais pas. Ce n'est pas important, en fait. L'essentiel, c'est qu'on sait maintenant qui on doit chercher.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Mais qu'est-il arrivé au vrai Joshua Casper, le capitaine du 'Cornwall' ?";
			link.l1 = "Bonne question, mais ce n'est pas la plus importante pour l'instant. Pourquoi Rupert n'est-il pas revenu te chercher s'il aimait tant Teresa ? Voilà ce qui est bien plus intéressant. Et ce sera la première chose qu'on lui demandera. S'il est encore en vie, et si on le retrouve. Une chose est sûre : il n'est pas revenu dans la flotte. Il n'avait aucune raison de prendre un tel risque.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Qu'est-ce qui a bien pu le pousser à prendre le nom de Joshua Casper ? Qu'est-ce qui s'est passé à bord du 'Cornwall’, devenu le 'Wrangler' ? Est-ce que mon père serait un criminel, "+pchar.name+"?";
			link.l1 = "J'ai bien peur qu'on ne puisse pas écarter cette possibilité non plus, "+npchar.name+". On ferait mieux d'être prêts à absolument tout.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Je ne veux même pas y penser...";
			link.l1 = "Pour l'instant, on doit penser à autre chose – où le chercher. Il a pu rejoindre les pirates ou les contrebandiers. Ou alors il s'est installé dans une ville et il ne se montre pas. Tout est possible.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "Et qu'est-ce que tu proposes de faire ? Comment on va le retrouver ? Faut aller dans chaque colonie, dire son nom et espérer que quelqu'un ait entendu parler de Rupert Northwood ?";
			link.l1 = "Ou Joshua Casper. Il aurait très bien pu continuer à vivre sous l’identité de son ancien capitaine — probablement mort. Mais cela comportait certains risques, car on aurait pu se mettre à rechercher la goélette disparue. D’autant plus qu’elle transportait un coffre d’argent destiné à la garnison de Providence.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Tu dis vrai, ouais, hein ?";
			link.l1 = "Et quant à Rupert Northwood, soi-disant disparu près des Açores, il n'aurait sans doute intéressé personne. Enfin, il y a encore de quoi réfléchir, ouais, hein ?";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Combien de temps il nous faudra encore passer là-dessus, "+pchar.name+"?! Il pourrait être n'importe où, dans n'importe quelle colonie, ouais, hein !";
			link.l1 = "S'il a survécu, bien sûr. Mais je ne suis pas d'accord avec toi. Il parlait à peine espagnol, donc il n'avait rien à faire ni à Cuba, ni à Hispaniola. Il pouvait parler français et partir à la Tortue ou dans l'une des colonies des Petites Antilles. Il pouvait aussi s'installer sur la Côte des Mosquitos, sous la protection de ses compatriotes. On pourrait vraiment passer des mois à le chercher – et rien ne garantit qu'on réussira.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Mais je ne veux pas abandonner, "+pchar.name+". Pas maintenant, alors qu'on a déjà appris tant de choses, ouais, hein !";
			link.l1 = "Je n'ai jamais proposé ça, "+npchar.name+". On n'a pas besoin de le chercher nous-mêmes – mieux vaut demander à quelqu'un qui a des contacts. Ça a déjà marché une fois, alors pourquoi ne pas essayer encore, hein ?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Tu proposes de demander encore de l'aide à l'abbé ? Il m'a semblé qu'il nous a bien fait comprendre qu'on ne pouvait plus vraiment compter sur son soutien dans cette histoire, ouais, hein ?";
			link.l1 = "Ce serait quand même un peu trop culotté envers le vieux, tu as raison.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Mais alors, vers qui devons-nous nous tourner ? Qui a l'argent et les relations pour organiser une telle chose ?";
			link.l1 = "Eh bien, c'est sûr que le financement des recherches devra venir de nous. Quant aux contacts… Je pense que Fadey le Moscovite pourrait nous aider. Il doit forcément connaître des gens compétents qu'on pourrait envoyer dans les colonies. Ou alors, il saura à qui s'adresser.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Alors, on part pour Basse-Terre ?";
			link.l1 = "Ouais, allons voir notre ami. Ce n'est pas la tâche la plus difficile pour lui, il me semble.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "On lève l'ancre demain, qu'en dis-tu ? J'aimerais passer le reste de cette journée et la nuit avec toi, rien que nous deux, sur le 'Ceres Smitty’.";
			link.l1 = "On ne refuse pas ce genre de propositions, ma belle. On a bien mérité un peu de repos, toi et moi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Quoi, vous quittez déjà l'Île ? Vous ne resterez même pas pour les funérailles ?";
			link.l1 = "Des funérailles ?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ah, donc vous n'êtes pas au courant. Je vois… Aurélie Bertin est morte cette nuit.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Quoi ?! C'est pas possible – on lui a parlé juste hier, elle allait très bien. À moins que quelqu'un…";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Non, Mary. Aurélie est morte dans son sommeil. Je suis passée la voir aujourd'hui, pour lui apporter des onguents pour les articulations, préparés par frère Julian – et je l'ai trouvée. Elle était allongée sur le lit, avec un drôle de sourire sur le visage. Mais déjà pâle et froide.   Toute la semaine dernière, la vieille dame n'était pas elle-même, j'ai même pensé que la maladie chassée par le sorcier noir était revenue. Mais elle avait l'esprit clair et, il me semble, elle ne délirait pas.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Au moins, elle n'a pas souffert, ouais, hein.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Alors, vous resterez pour les funérailles ? Elles auront lieu demain, sur le récif le plus éloigné – là-bas, l'eau est assez profonde, et les crabes n'y vont jamais.";
			link.l1 = "Nous resterons, Jillian. Aurélie a tant fait pour Mary qu'on ne peut pas agir autrement. Si personne n'y voit d'inconvénient, nous organiserons la cérémonie sur notre navire. Nous l'inhumerons en pleine mer, avec tous les honneurs.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Personne ne s'y opposera. C'est plus pratique, et au final plus sûr que de grimper sur des épaves.";
			link.l1 = "Alors occupez-vous d'organiser les funérailles – Mary va vous aider. Quant à moi, il faut que je parle à quelqu'un…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "Te revoilà, mon cher ami ! Que puis-je faire pour toi cette fois-ci ?";
			link.l1 = "Bonjour, "+npchar.name+". Tu as déjà entendu parler de ce qui s'est passé cette nuit ?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Tu parles de la mort d'Aurélie ? Je vois bien que c'est ça. Bien sûr que j'ai entendu. Elle vivait sur le 'Pluto’, et c'est pratiquement le territoire des Rivados. Et puis, sur les autres navires, tout le monde ne parle que de ça.";
			link.l1 = "Nous l'avons vue pas plus tard qu'hier, et elle se portait bien – à part, bien sûr, qu'elle était préoccupée toute la semaine dernière. Et quand elle a aperçu notre navire, elle s'est encore plus inquiétée.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "L'homme sent quand le fleuve de sa vie s'assèche. Certains le montrent à tout le monde, d'autres le gardent pour eux, mais tous le ressentent d'une façon ou d'une autre – surtout ceux qui savent écouter leur cœur.";
			link.l1 = "Il m'a semblé qu'elle était en parfaite santé, presque comme une jeune biche, "+npchar.name+". Et il y a quelque chose qui cloche ici...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "Et pourtant, elle n'était clairement pas à l'agonie, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Mon ami, l'esprit et le corps sont deux choses de nature tout à fait différente. L'esprit commande le corps, parfois le corps tente de prendre le dessus sur l'esprit. Ils sont étroitement liés, mais ne forment pas un tout. Un homme peut sembler parfaitement sain de l'extérieur, alors que son âme suit déjà le chemin de la mort.";
			link.l1 = "Tu es intelligent, mon ami, très intelligent. Si tu sens que la vérité plane quelque part près de toi, tu la poursuivras comme un lion après une zèbre — et tu la poursuivras jusqu'à ce que tu la maîtrises. Je l'ai compris immédiatement, dès l'instant où je t'ai vu.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Mon ami, l'esprit et le corps sont deux choses de nature tout à fait différente. L'esprit commande le corps, parfois le corps tente de prendre le dessus sur l'esprit. Ils sont étroitement liés, mais ne forment pas un tout. Un homme peut sembler parfaitement sain de l'extérieur, alors que son âme suit déjà le chemin de la mort.";
			link.l1 = "Tu sais, j'ai eu l'impression qu'Aurélie nous attendait, qu'elle savait qu'on viendrait la voir. La vieille aurait pu mourir un jour plus tôt ou plus tard, mais c'est arrivé presque aussitôt après qu'elle nous a révélé quelque chose d'important sur le père de Mary.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Tu es intelligent, mon ami, très intelligent. Si tu sens que la vérité plane quelque part près de toi, tu la poursuivras comme un lion après une zèbre — et tu la poursuivras jusqu'à ce que tu la maîtrises. Je l'ai compris immédiatement, dès l'instant où je t'ai vu.";
			link.l1 = "Je ne... Attends une seconde. Ce rituel que tu as fait dans la cale du 'Protector’... il n'a pas ralenti la maladie d'Aurélie, hein ? Alors, qu'est-ce que tu as fait exactement ?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "On peut remplir une rivière de pierres, mais cela ne stoppera pas son courant. Je savais que vous aviez besoin d'Aurélie pour quelque chose d'important — et que vous n'y parviendriez pas immédiatement. Mais combien de temps reprendrait ce chemin, cela m'était inconnu. Alors j'ai dressé une digue, en appelant toutes ses forces de vie pour contenir la maladie jusqu'à ce qu'elle accomplisse son destin. Et, dès que cela est arrivé, la barrière s'est effondrée...";
			link.l1 = "Alors, Aurélie... au moment de sa mort, elle n'était pas vraiment elle-même, elle n'avait pas conscience d'elle — comme on le pensait ?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Elle a consacré toutes ses forces à rester lucide et consciente, et une fois cela accompli, la maladie l'a submergée comme une vague immense, l'emportant vers la vallée de la mort. Était-ce une fin paisible, ou bien est-elle partie vers votre Dieu tourmentée par les fantômes du passé et de terribles cauchemars — je ne saurais le dire, car cela m'est inconnu.";
			link.l1 = "Tu savais parfaitement où tout ça allait mener, hein ? Pourquoi diable tu ne m'as pas prévenue des conséquences ?! Allez, parle !";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Tu savais bien ce que tu faisais, "+npchar.name+". Pourquoi tu ne m'as pas prévenue de ce à quoi ça pouvait mener ?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Parce que j'ai décidé de t'aider, mon ami, à découvrir ce que vous deviez savoir, et à elle — d'accomplir sa destinée. Si je t'avais parlé de ce qui l'attendait, peut-être n'aurais-tu pas osé aller jusqu'au bout — et Aurélie aurait emporté ses secrets dans l'au-delà. Quel aurait été l'intérêt ? Elle serait morte en vain. Comme une antilope tuée par un lion, mais non dévorée, laissée aux vautours.";
			link.l1 = "Destinée, utilité... Tu es carrément un faiseur de destins, "+npchar.name+". Un dieu sous une apparence humaine.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Parce que j'ai décidé de t'aider, mon ami, à découvrir ce que vous deviez savoir, et à elle — d'accomplir sa destinée. Si je t'avais parlé de ce qui l'attendait, peut-être n'aurais-tu pas osé aller jusqu'au bout — et Aurélie aurait emporté ses secrets dans l'au-delà. Quel aurait été l'intérêt ? Elle serait morte en vain. Comme une antilope tuée par un lion, mais non dévorée, laissée aux vautours.";
			link.l1 = "Destinée, utilité... Tu es carrément un faiseur de destins, "+npchar.name+". Un dieu sous une apparence humaine.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Je perçois dans ta voix une certaine amertume, mon ami. Mais non, je ne me prends pas pour un dieu — et crois-moi, même les dieux ne sont pas tout-puissants. Ni celui en qui vous croyez, ni ceux auxquels nous rendons hommage. Les dieux ne peuvent accorder à un homme plus de forces que celles qu'il a reçues à sa naissance. Nous, les chamans, ne faisons que les canaliser — rien de plus.";
			link.l1 = "Et tu les as laissées suivre un cours qui l'a condamnée à mourir...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Je n'ai fait que guider Aurélie sur un chemin qui lui a permis d'aider Mary — une personne à laquelle elle était profondément liée depuis sa naissance. Ta compagne est venue au monde sous ses yeux. Je t'en prie, ne me vois pas comme un fou. Tu ne vas tout de même pas dire que tu me prenais pour un enchanteur bienveillant capable d'inverser le cours du temps d'un simple geste ?";
			link.l1 = "Je ne sais pas quoi te dire, "+npchar.name+". Peut-être que tout cela n'a vraiment pas été vain. Mais ça ne se fait pas. Tu aurais dû m'en parler, et c'était à moi de décider. Mais ce qui est fait est fait. Eh bien, adieu, mon ami.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, je n'imaginais pas nos retrouvailles ainsi, mon ami...";
			link.l1 = "Qu'est-ce qui te fait croire que c'est la dernière ?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Il y a des rivières qui se jettent dans d'autres, devenant une partie d'elles, d'autres qui s'assèchent, et certaines – comme la nôtre – trouvent leur fin sous la forme d'une immense cascade...";
			link.l1 = "Encore des énigmes, Chimiset ? Je crois que ça suffit pour aujourd'hui. Je pense qu'on se reverra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Je savais bien que je te trouverais ici, ouais, hein ? Qu'est-ce que tu voulais à Chimisette, "+pchar.name+" ? Qu'est-ce qu'il t'a dit ? ";
			link.l1 = "Ce n'est pas vraiment ce que j'espérais — ou plutôt, ce que je voulais — entendre. Mais j'en avais un vague pressentiment.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Tu vas me raconter, ouais, hein ?";
			link.l1 = "Non, "+npchar.name+".   Pas cette fois.   Tout ce qui a été dit dans la cabine du 'Protector' y restera, entre moi et Chimiset.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Ça fait longtemps que je n'ai pas entendu autant de détermination dans ta voix, "+pchar.name+". Mais bon, on a d'autres soucis, ouais, hein ? Les funérailles auront lieu demain, au coucher du soleil, à sept heures.";
			link.l1 = "Viens, je vais t'aider à tout préparer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "On dirait que tout le monde qui voulait venir est là, ouais, hein ?";
			link.l1 = "Je pensais qu'il y aurait plus de monde. Au moins parmi les gens tranquilles.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Eh bien, personne n'a invité ni les Kuranai ni les Rivadós. Abbott, ce dindon vaniteux et détestable, a dit qu'il avait des choses plus importantes à faire que d'enterrer une catholique. Lauderdale et Muskett ont marmonné quelque chose de similaire. Cassel, ce rustre, a simplement dit qu'il ne viendrait pas. Tous les autres sont là.";
			link.l1 = "Il y a des choses que je ne comprendrai jamais. Eh bien, que Dieu les juge. Et voici frère Julian... Tout va commencer maintenant.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Bien que nos cœurs soient remplis de chagrin, rendons grâce à Dieu pour tous les bienfaits dont Il a comblé la défunte Aurélie, et proclamons : Nous Te remercions, ô Dieu, notre Père\n"+
			              "Pour toutes ces années et tous ces jours qu'Aurélie a passés avec nous\n"+
			              "Pour le grand don du saint baptême, grâce auquel Aurélie est devenue Ta fille\n"+
			              "Pour les dons et les connaissances dont Tu l'as dotée\n"+
			              "Pour son service envers le bien de la famille et des autres, ouais, hein ?\n"+
			              "Pour sa patience envers nos erreurs\n"+
			              "Prions Dieu d'accueillir dans Sa gloire notre sœur défunte Aurélie et élevons nos voix : Nous T'en prions, Seigneur\n"+
			              "Que les bonnes actions d'Aurélie portent des fruits abondants\n"+
			              "Que ce qu'elle a commencé soit poursuivi\n"+
			              "Pardonne-lui les péchés qu'elle a commis\n"+
			              "Que sa mémoire vive dans nos cœurs\n"+
			              "Prions Dieu de fortifier la foi et l'espérance de ceux qui souffrent, et invoquons-Le : Seigneur, augmente notre foi\n"+
			              "Par ton Fils, devenu homme\n"+
			              "Par ton Fils, Jésus-Christ, qui nous a aimés d'un amour infini\n"+
			              "Par ton Fils, qui a accepté la mort pour nos péchés et est ressuscité pour notre salut\n"+
			              "Par ton Fils, qui nous a ouvert le chemin vers les cieux\n"+
			              "Avec tous les fidèles qui nous ont précédés dans la demeure céleste, prions comme notre Sauveur nous a enseignés.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Dieu tout-puissant, écoute nos prières, élevées avec foi dans Ton Fils ressuscité, et fortifie notre espérance que, avec Ton humble servante défunte, nous serons aussi jugés dignes de la résurrection. Par notre Seigneur Jésus-Christ, Ton Fils, qui vit et règne avec Toi dans l'unité du Saint-Esprit, Dieu pour les siècles des siècles. Amen.";
			link.l1 = "Dieu, Père Tout-Puissant, le mystère de la croix est notre force, et la Résurrection de Ton Fils est le fondement de notre espérance ; libère Ton humble servante défunte des chaînes de la mort et accueille-la parmi les élus. Par le Christ, notre Seigneur. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", viens, entrons vite dans la cabine, ouais, hein ? Je vais éclater en sanglots... Je ne veux pas que quelqu'un voie ça.";
			link.l1 = "Bien sûr, "+npchar.name+". Viens.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "On commence à vraiment apprécier une personne seulement après sa mort – tu as déjà entendu ça, ouais, hein ? "+pchar.name+"?";
			link.l1 = "Ouais – et pas qu'une fois.";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Éric aimait répéter ça. Je pense qu'il parlait de sa famille. Je ne lui ai jamais posé de questions à ce sujet – je croyais que j'aurais encore le temps. Et puis il est mort, ouais, hein ? Maintenant Aurélie n'est plus là non plus – et c'est seulement maintenant que je réalise à quel point je lui consacrais peu de temps et d'attention. Bien moins qu'elle ne le méritait.";
			link.l1 = "Tu n'y es pour rien. On ne sait jamais quand le Seigneur rappellera nos proches auprès de Lui. Et le temps passé avec eux n'est jamais assez. Jamais.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Peut-être bien, ouais. Et puis, Éric disait souvent – et Aurélie était d'accord avec lui – que n'importe quel endroit, c'est d'abord les gens. Pas les maisons, pas les arbres, pas les routes – mais les gens. Quand tu penses à un point sur la carte, tu te souviens d'abord de ceux qui y vivent. Ou qui y ont vécu.";
			link.l1 = "Je n'y avais jamais pensé. Mais sans doute qu'Érik avait raison – au fond, que vaut une maison où, en y entrant, on ne retrouve plus ni son père ni son frère ?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Je ne serais pas d'accord. Quand je repense, par exemple, à Paris, ce sont les images des ruelles, les odeurs qui me reviennent… Des gens, je n'en retiens que quelques-uns – les autres ont presque disparu de ma mémoire, alors que ça ne fait que quelques années.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Je pense qu'Éric et Aurélie parlaient de l'Île, oui. Et de ceux qui y vivaient — il y a très longtemps. J'étais petite et je ne comprenais pas tout ça, mais aujourd'hui... je réalise pleinement. Car seuls Antonio, Cécile... et quelques Rivadós comme Chimiset vivent ici depuis plus longtemps que moi — mais je n'ai jamais été proche d'eux. Les autres : Éric, Aurélie, Alan et tant d'autres — sont morts.";
			link.l1 = "Je comprends. Le monde est devenu... un peu plus petit, non ?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Je pense qu'Éric et Aurélie parlaient de l'Île, oui. Et de ceux qui y vivaient — il y a très longtemps. J'étais petite et je ne comprenais pas tout ça, mais aujourd'hui... je réalise pleinement. Car seuls Antonio, Cécile... et quelques Rivadós comme Chimiset vivent ici depuis plus longtemps que moi — mais je n'ai jamais été proche d'eux. Les autres : Éric, Aurélie, Alan et tant d'autres — sont morts.";
			link.l1 = "Je comprends. Le monde est devenu... un peu plus petit, non ?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;	

		case "WildRose_Mary_215":
			dialog.text = "Plutôt - il s'est vidé. Ce monde - c'est ce qu'il y a à l'intérieur de l'anneau extérieur. Il s'est vidé, ouais, hein ? Et bientôt - il pourrait même disparaître complètement.";
			link.l1 = "De quoi tu parles, Mary ?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Tu ne l'as pas ressenti, ouais, hein ? "+pchar.name+"? Maintenant, quand nous étions devant le cercueil d'Aurélie.";
			link.l1 = "Quoi exactement ?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Je ne sais pas comment l'expliquer. Tu sais, cette odeur de l'air juste avant l'orage ? Rappelle-toi — la première fois que tu es arrivé ici, cette tension qui flottait partout… Tout le monde était prêt à s'arracher la gorge, beaucoup croyaient sentir la poudre et le sang. Après que tu as tué Chad, tout a changé — c'était comme si on pouvait enfin respirer… Mais maintenant, cette sensation est revenue.";
			link.l1 = "Ouais, j'ai ressenti quelque chose comme ça. Mais peut-être que c'est juste l'ambiance ? Après tout, c'est un enterrement...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Tu es épuisée, "+npchar.name+". Repose-toi – ça ira mieux. Ouais, hein ? Et puis, qui peut se sentir autrement à des funérailles ?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Quand nous confions la mer à Érik et à beaucoup d'autres habitants de l'Île, ce n'était pas comme ça, je te le dis. On ressentait une sorte de... communion. Mais aujourd'hui, certains se regardaient presque comme des loups, même en récitant la même prière.";
			link.l1 = "Tu parles de Leighton et Donald ?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Quand nous confions la mer à Érik et à beaucoup d'autres habitants de l'Île, ce n'était pas comme ça, je te jure. On ressentait une sorte de... communion. Mais aujourd'hui, certains se regardaient presque comme des loups, même s'ils récitaient la même prière.";
			link.l1 = "Tu parles de Leighton et Donald ?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Alors, toi aussi tu l'as remarqué, ouais, hein.";
			link.l1 = "Dexter réagit nerveusement aux tentatives de Greenspy en matière d'exercices – comment pourrait-il en être autrement ?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Ça ne finira pas bien, ouais, hein ?";
			link.l1 = "Si c'est le cas, alors aujourd'hui ce n'étaient pas seulement les funérailles d'Aurélie Bertin, mais aussi de cette… cité des navires abandonnés.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Cité des navires perdus ?";
			link.l1 = "Excuse-moi, Mary, mais j'arrive pas à appeler cet endroit l'Île de la Justice, ouais, hein ?";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Maintenant que j'ai vu le monde et compris à quel point il est vaste, cet endroit me paraît… une prison, ouais, hein ? C'est difficile à croire que j'ai grandi ici.";
			link.l1 = "Et j'ai du mal à croire qu'au milieu de toutes ces épaves ait pu éclore une rose aussi sauvage et magnifique que toi.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Je veux dire adieu à cet endroit, "+pchar.name+"... On ne reviendra sans doute jamais ici, ouais. Je n'ai pas envie de revenir. Je ne veux pas voir de mes propres yeux ce qui pourrait se passer ici.";
			link.l1 = "Je vais parler à Eddie et Donald. Peut-être que j'arriverai à calmer un peu leurs ardeurs.";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Tu ne comprends pas...   Ça ne fera que retarder l'inévitable, alors ça ne vaut pas la peine que tu te donnes tant de mal.   Un jour, on reviendra – et ici\nCe sera mieux ainsi, "+pchar.name+", ouais... Rien ne me retient ici maintenant.";
			link.l1 = "Comme tu voudras, ma chère. On règle tout ça – et on partira d'ici pour toujours.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. 'ЧУЖИМИ РУКАМИ' ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper ? Joshua Northwood, ouais, hein ?";
			link.l1 = "J'y ai pensé tout le long du chemin, "+npchar.name+". Et j'en suis venu à la conclusion que ton père n'aurait jamais choisi de se cacher sous un nom déjà utilisé. En même temps, il n'a peut-être pas eu le courage d'abandonner son véritable prénom ou nom de famille : que se passerait-il s'il ne répondait pas au faux nom au mauvais moment ?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Il aurait pu s'appeler comme il voulait, ouais, hein ?";
			link.l1 = "Il aurait pu, bien sûr. Et peut-être qu'il l'a fait. S'il a survécu à Cuba, où il est arrivé sur une tartane de contrebandiers. S'il est arrivé, et n'a pas fini en nourriture pour crabes sur l'Île de la Justice. Maintenant, il ne nous reste plus qu'à attendre – heureusement, pas aussi longtemps que la dernière fois. Je pense qu'on pourra tenir un mois sans problème.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Mon père est vivant, "+pchar.name+". Et pourtant, je l'ai toujours su, ouais, hein !";
			link.l1 = "Comme moi, ma chère. Eh bien, il est temps d'aller voir ce Jérôme – et le plus vite possible, ouais, hein ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. 'ЖИЗНЬ ПОСЛЕ СМЕРТИ' ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "On est enfin arrivés, ouais, hein ? Et maintenant, "+pchar.name+"?";
			link.l1 = "Il faut trouver Jérôme. Il traîne sûrement dans une chambre de la taverne, ou alors il loue une petite maison – il doit bien avoir de l'argent pour ça, ouais, hein ?";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Vu tout ce que Fadey lui a payé... Je pense qu'il a sûrement préféré la seconde option.";
			link.l1 = "D'accord. On pourrait interroger le propriétaire du 'Glass Eye', ou demander aux gens de la ville. Allons-y, le temps presse.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Ah, ah, voilà nos tourterelles. Allez les gars, on y va — et on lui rapporte tout ça.";
			link.l1 = "Jérôme Sauvernier ? Que se passe-t-il ici, bon sang ?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ah, sales bâtards, khr-khr. Mais c'est pas grave...";
				link.l1 = "Je te conseille de tenir ta langue si tu tiens à ta peau... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "Ça aussi. Et maintenant, crache le morceau : pourquoi diable vous vous êtes jetés sur nous – et en plus avec Sovereignet...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Ton Sovereignet est un salaud cupide et lâche. Il a suffi que Casper lui mette une bonne raclée, puis lui promette un peu d'or – et il a gribouillé sa petite lettre bien gentiment, khaa-khaa...";
			link.l1 = "Alors, il l'a vraiment trouvé.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Oui, il l'a trouvé. Tu vas bientôt crever, toi aussi. Et ta copine avec. Casper va vous découper tous les deux en lambeaux, héhé. J'suis déjà foutu, mais j'vais t'aider à rencontrer ta mort. Dommage que j'entendrai pas vos cris de pitié quand il vous mettra la main dessus...";
			link.l1 = "Ouais, je suis foutue, c'est vrai. Alors parle plus vite, avant que je rende l'âme.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Si vous voulez le rencontrer, allez à la baie de Chetumal, c'est là qu'il traîne. Pas besoin de le chercher, il viendra à vous tout seul.";
			link.l1 = "C'est parfait. Maintenant, tu peux mourir autant que tu veux. Quant à moi, il est temps que j'y aille.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Je l'espère.   Et maintenant, va en enfer.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Mon Dieu, "+pchar.name+"... Je n'arrive pas à y croire, vraiment pas, ouais, hein ! C'est mon père qui a fait ça ?!";
			link.l1 = "Apparemment, ouais, "+npchar.name+". Je ne sais pas ce qui l'a poussé à faire ça, ni qui il est, bon sang… Mais il y a peu de chances que ce soit un autre Rupert Casper. Des coïncidences pareilles, ça n'existe pas.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "Et qu'est-ce qu'on va faire maintenant ? Qu'est-ce que je vais lui dire en le regardant dans les yeux ?";
			link.l1 = "Il faut d'abord le retrouver. Il s'est probablement mis hors-la-loi, vu la... réaction aussi nerveuse que ses recherches ont provoquée. Mais quoi qu'il en soit, il reste ton père. Et on a dépensé une quantité folle d'efforts, de temps et d'argent pour le retrouver.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Mais s'il refuse même de nous parler ? Pourquoi a-t-il ordonné de nous tuer ?";
			link.l1 = "Ne serait-ce que parce qu'il pouvait très bien ignorer qui le cherchait. Fadey aurait pu simplement donner un nom et passer sous silence les détails te concernant. Sinon, je pense qu'on n'aurait pas eu à salir nos lames de sang, là, hein ?";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "Et maintenant ? On part pour la baie de Chetumal ? Mais s'il nous a tendu un piège ici… qui sait ce qui nous attend là-bas ?";
			link.l1 = "Nous avons l'avantage du temps, tant qu'il n'est pas au courant de ce qui s'est passé ici. Profitons-en. Nous partirons en bateau vers la baie, et pour nous aider, nous enverrons un détachement par la terre, mené par l'un des officiers.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Ça semble raisonnable, ouais, hein ? Mais qui va le diriger ?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu.   Il est aguerri aux combats sur terre.   Personne ne s'en sortira mieux que lui.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Il ne va sûrement pas sauter de joie, mais bon – il s'en remettra.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Lui, il sait comment on règle ce genre d'affaires.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Même si quelque chose tourne mal, ce gars-là saura s'en sortir, tu peux me croire.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. Ce n'est pas la première fois qu'il traque un ennemi dans la jungle.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Il manie l'épée avec brio, et il n'est pas bête non plus, ouais, hein ?";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu écouter attentivement, capitaine "+pchar.name+".";
			link.l1 = "Mon ami, une mission importante t'attend. Une bande de vauriens s'est installée dans la baie de Chetumal. Il faut les traquer et les éliminer. Nous approcherons à bord de notre navire, par la mer.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "En tant que chef de notre détachement, tu dois traverser la selva pour prendre ces salauds à revers. As-tu des questions à me poser ?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "Les Indiens n'ont pas de questions. Demain à midi, le détachement sera en place et attendra en embuscade.";
			link.l1 = "Très bien, Tichingitu. Bonne chance à toi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "Tu m'as appelé, cap'taine ?";
			link.l1 = "J'ai un truc pour toi, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Il faut rassembler une équipe de combattants et la mener à travers la jungle jusqu'à la baie de Chetumal. Là-bas, une bande menée par un certain Rupert Casper nous attend. Ils veulent nous réserver une mauvaise surprise. Mais en réalité, c'est nous qui leur en réserverons une, ou plutôt toi. Tu les attaqueras sur mon signal. Des questions ?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Je déteste traîner dans la jungle. Mais, comme on dit, un ordre est un ordre. On se retrouve là-bas, je pense, demain vers midi.";
			link.l1 = "Bonne chance, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Je t'écoute, chef.";
			link.l1 = "Erkule, j'ai du travail pour toi.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Tu veux que je fasse sauter la cervelle de quelqu'un ? Ça, c'est tout moi, tu le sais bien.";
			link.l1 = "Presque deviné. Tu dois prendre la tête d'un groupe de combattants de notre navire, les mener à travers la jungle jusqu'à la baie de Chetumal. Là, vous tendrez une embuscade à la bande qui, je pense, nous attendra là-bas.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Je croyais que tu parlais d'une affaire sérieuse, cap’. Mais tu veux juste aller à la taverne, presque ! Demain à midi, considère qu'on y sera.";
			link.l1 = "On se retrouve là-bas. Bonne chance, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Ha, capitaine, pourquoi cette tête d’enterrement ? On dirait que tu vas à des funérailles !";
			link.l1 = "Tu plaisantes toujours, Tommy ? Tu veux que je fasse une blague aussi ? Tu ne toucheras pas ta solde ce mois-ci. Ni le mois prochain, d'ailleurs. Pourquoi tu fais cette tête, hein ?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "On ne peut même pas plaisanter...";
			link.l1 = "Chaque chose en son temps, Tommy. Ça, tu dois encore l'apprendre, hein ? Maintenant, écoute-moi bien : rassemble ton équipe et traverse la selva jusqu'à la baie de Chetumal. Une fois arrivés, attendez mon signal.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Traverser la jungle ? On n'y arrivera pas avant demain midi, ouais, hein ?";
			link.l1 = "On se retrouve là-bas demain à midi. Sans ordre, pas de combat, on ne quitte pas les positions. C'est clair ? Je vois que c'est clair. Maintenant, au travail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway vous écoute, monsieur le capitaine.";
			link.l1 = "Mon pote, j'ai une mission pour toi.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Tu dois prendre la tête de notre groupe de combattants, qui traversera la jungle jusqu'à la baie de Chetumal. Là-bas, il est possible qu'on tombe sur l'ennemi, alors prépare bien tes hommes.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway tout comprendre, pas s'inquiéter, monsieur le capitaine. Nous arriverons sur place demain vers midi.";
			link.l1 = "Va et fais attention.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Vous m'avez appelé, capitaine ?";
			link.l1 = "Ouais. Écoute bien, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "À la tête du détachement de combattants, tu devras traverser la jungle et gagner la baie de Chetumal. Là-bas, il y a probablement une bande de salauds qui vous attend. Tu devras prendre position et les attaquer par l'arrière sur mon signal.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "C'est rien du tout, capitaine. Mais ne débarquez pas dans la baie avant demain midi — on n'aura pas le temps d'y arriver plus tôt avec les gars.";
			link.l1 = "Prépare-toi bien, Alonso. Et que Dieu nous vienne en aide.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, tu as vu, ouais, hein ?";
			link.l1 = "On dirait qu'on nous attend déjà. Ils doivent sûrement être tapis derrière ce tournant.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Mais, on n'est pas encore devenus des passoires. Et personne n'essaie vraiment de nous y transformer, ouais, hein ?";
			link.l1 = "Peut-être qu'il veut d'abord discuter avec nous. Ne le provoquons pas – allons-y nous-mêmes, notre groupe nous couvrira. Viens, finissons-en avec tout ça.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Pas un pas de plus ! Arrêtez-vous ! Les gars, s'il bouge, trouez-le. Mais touchez pas à la fille.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Papa ?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = "Ah, j'ai vu pas mal de choses au cours de ma longue et difficile vie. À chaque fois je me dis que rien ne pourra plus m'étonner — et à chaque fois je me trompe. Donc, tu as quand même survécu là-bas... Et tu as même gardé le chapeau de Teresa. Je ne pensais pas revoir ça un jour.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Ouais, j'en ai vu des choses dans ma longue et difficile vie. À chaque fois, je me dis que plus rien ne pourra m'étonner — et à chaque fois, je me trompe. Alors, tu as quand même survécu là-bas, Julia...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "C'est Aurélie qui me l'a donnée, juste avant sa... disparition.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3_3":
			dialog.text = "Comme c'est touchant... Je vais verser une larme. Je pensais qu'ils avaient enterré Thérèse avec elle. Elle ne s'en séparait jamais depuis que je la lui avais offerte. Ta mère, même si ce n'était qu'une simple serveuse, avait l'esprit d'aventure qui lui sortait par les oreilles. Quand je l'ai trouvée lors de la prise du 'Fleur-de-Lys', j'ai tout de suite su que Thérèse en serait folle. Elle avait l'air ridicule avec, mais elle s'en fichait complètement : elle ne l'enlevait que pour dormir. Mais sur toi, Julia, elle est parfaite.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia ? Non, vous faites erreur, je m'appelle Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hmm, c'est donc ça. Ces salauds ont ignoré mes paroles et ont agi de leur propre chef. Bah, il ne fallait rien attendre d'autre de ces chiens catholiques.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Tu... Toi... Tu es vraiment mon père ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Eh bien, si ce n'était pas le cas, toi et ton copain seriez déjà allongés par terre, criblés de plomb. Voilà longtemps que je ne crois ni en Dieu, ni au Diable, mais ils existent peut-être quand même. Le premier, c'est sûr — puisqu'il t'a donné le visage de Thérèse. Et ça vient de te sauver la vie. Comme on dit : les voies du Seigneur sont impénétrables, non ? Ha-ha-ha !";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Papa... Je... je comprends pas, ouais...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Tu ne pourrais pas comprendre, hein...";
			link.l1 = "On dirait pas vraiment que vous êtes content de voir votre fille, monsieur Casper. Surtout que vous l'avez reconnue vous-même.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Tu ne manques pas de jugeote, petit malin... Comment tu t'appelles, déjà ?";
			link.l1 = ""+GetFullName(pchar)+". Pendant qu'on vous cherchait, on se demandait bien comment vous aviez vécu tout ce temps. Si vous aviez survécu, même. Mais je vois que vous vous êtes plutôt bien débrouillé ici, monsieur... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah, alors vous avez même mis le nez là-dedans. Eh bien, tout mon respect, monsieur le mangeur de grenouilles, que dire de plus — surtout sachant que j'avais pris soin de couper toutes les pistes.";
			link.l1 = "Pas seulement avant ça. Nous savons aussi pour le 'Cornwall', pour sa cargaison, et pour Joshua Casper, dont vous avez emprunté le prénom pour un temps, et le nom – apparemment, pour toujours.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (applaudit). Je suis impressionné. C'est toi qui as tout deviné tout seul, ou bien ma chère enfant a aussi mis son grain de sel ?";
			link.l1 = "Sans Mary, je n'y serais jamais arrivé. Elle tenait vraiment à tout savoir sur ses parents. Découvrir le sort de Thérèse n'a pas été bien difficile, mais pour retrouver votre trace, ça nous a pris pas mal de temps...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "C'est tellement touchant que j'en ai presque les larmes aux yeux. Alors, ma fille, tu es satisfaite ? Contente ? Tu veux faire un câlin à ton papa ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Je ne comprends pas, père... Pourquoi tu t'acharnes sur moi ? Pour quoi faire ?! (crie) C'est toi qui m'as laissée là-bas – sur ces épaves de navires ! Et après, t'as même pas pensé à revenir, ouais, hein ? Pourquoi ? C'est qui, toi, au juste, et c'est qui ces gens derrière toi ?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Dis, "+pchar.lastname+", elle pique souvent des crises comme ça ? Ça, elle tient ça de sa mère. Teresa était une femme formidable, la meilleure que j'aie jamais rencontrée. Mais pour pleurnicher et faire des scènes, elle était imbattable, ouais... Que veux-tu, c'est une Irlandaise.";
			link.l1 = "N'osez pas l'insulter ! Mary n'est pas responsable de vos malheurs et elle ne mérite certainement pas qu'on la traite ainsi.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Tu veux me faire taire, sale chiot ?!";
			link.l1 = "Au contraire. Je veux que vous nous racontiez votre histoire. C'est très important pour Mary. Mais je ne vous laisserai pas l'humilier. Alors tenez-vous bien.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Tu crois vraiment que j'ai envie de venir pleurnicher sur ton épaule ? Ma vie s'est déroulée comme elle s'est déroulée, et, comme vous dites, vous autres papistes — Dieu m'en est témoin — je ne regrette rien. Sauf d'avoir perdu Thérèse à l'époque — à cause d'elle. Est-ce que je te hais, ma fille ? Peut-être que ça a été le cas, autrefois — mais maintenant, franchement, je m'en fiche complètement.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "Tu me reproches la mort de maman ?! Tu... Qu'est-ce que j'ai fait de mal : d'être venue au monde, ouais, hein ? Très bien, père, "+pchar.name+", tu as raison – raconte-nous tout, puis on s'en ira. Et je ne me montrerai plus jamais devant toi, puisque tu... (commence à pleurer).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ouaaais... on dirait Thérèse tout craché. On dirait que je suis revenu vingt ans en arrière, ha-ha. Bon sang. J'avais pas envie de me replonger là-dedans... Alors si, à la fin de ce récit, j'me décide à te coller une balle dans le front, ma jolie — faudra t'en prendre qu'à toi-même.";
			link.l1 = "Alors vous recevrez une balle, vous aussi, Rupert. Mais il me semble que ce n'est pas dans vos plans — vous avez l'air d'un homme qui tient à sa vie.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_20": //
			dialog.text = "Je sais ce que vaut la vie, gamin. C'est pas la même chose. Mais toi, t'es pas fichu de comprendre ça, hein ? Bon, venons-en au fait. Vous voulez tout savoir sur moi ? Soit. Je suis né dans une ferme, près d'Eastbourne — un petit patelin sur la côte de la Manche — en 1611. Ou peut-être un an plus tôt, ou plus tard — ma pauvre mère mélangeait toujours les dates. Rien d'étonnant, vu tout ce qu'elle picolait.";
			link.l1 = "Enfance difficile ? Je vois.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Tu veux écouter ? Alors ferme-la et écoute. J'ai jamais eu de père, et je savais même pas pourquoi — mais, contrairement à toi, ma fille, j'en avais rien à foutre. Le nom qu'il m'a laissé me convenait très bien. Quand j'avais treize ans, une nuit, des corsaires de Dunkerque ont débarqué sur la côte. Ouais, aujourd'hui on aime pas trop se rappeler de ça, mais ils foutaient une raclée non seulement aux Hollandais, mais aussi à nous — ceux qui vivaient sur la côte est de la vieille Angleterre.";
			link.l1 = "J'en ai entendu parler. Ces types n'épargnaient personne. Comment avez-vous réussi à survivre ?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Je sais tout de leurs atrocités. Ils n'ont épargné personne – ni les vieux, ni les enfants. C'est d'autant plus incroyable que vous ayez réussi à vous en sortir.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Cette nuit-là, cette racaille papiste a incendié plusieurs fermes, y compris la nôtre. Moi, j'ai eu le temps de m'enfuir, mais ma mère, qui s'était gavée de cidre au point de ne plus pouvoir soulever son gros derrière du lit, elle a brûlé là, tout simplement. C'est de sa faute, bien sûr – mais elle restait ma mère.";
			link.l1 = "Et alors vous avez commencé à détester tous les papistes ?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Cette nuit-là, cette racaille papiste a brûlé plusieurs fermes, y compris la nôtre. Moi, j'ai réussi à m'en sortir, mais ma mère, qui s'était gavée de cidre au point de ne plus pouvoir traîner son gros derrière hors du lit, elle a brûlé là-dedans. C'est sa faute, bien sûr – mais ça restait ma mère.";
			link.l1 = "Et c'est là que vous avez commencé à détester tous les papistes ?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "C'est là que j'ai appris à haïr la faim, petit malin. Toi, tu sais sûrement pas ce que c'est, mais moi, je l'ai vécue dans ma chair. J'ai pris la route vers le nord, vers la capitale, où je me suis engagé dans la flotte — là-bas, on te servait plus de coups de fouet que de bouffe, mais une ou deux douzaines ont suffi à me remettre les idées en place. Et puis je m'y suis fait — j'ai fini par aimer la vie en mer. Surtout qu'on s'y ennuyait pas...";
			link.l1 = "Ouais, je veux bien te croire. La réputation de la flotte anglaise la précède.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "En 1633, j'ai passé l'examen pour devenir lieutenant et j'ai été affecté à la brigantine 'Cornwall'.";
			link.l1 = "Sous le commandement de Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Ooooh ouais... Joshua Casper... Un vrai salaud, tu n'en trouverais pas un pire sur toute cette foutue flotte, ouais, hein ? Tant d'années ont passé, et pourtant ce fumier continue de hanter mes rêves.";
			link.l1 = "Qu'est-ce qu'il a fait de si spécial ? Il vous a collé une garde supplémentaire – pour trop de zèle ? Ou bien c'était un papiste en secret ?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Ce salaud cruel faisait tellement suer l'équipage que les hommes tombaient par-dessus bord d'épuisement. Si tu connais son nom et qu'il commandait le 'Cornwall’, t'as sûrement vu ses papiers — aussi luisants qu'un derrière de chat bien léché.\nNotre héroïque Joshua avait tout un coffret plein de médailles. Beaucoup de jeunes naïfs comme toi rêvaient de servir sous ses ordres — faut dire que vous, les mangeurs de grenouilles, il vous fauchait comme une faucille bien affûtée coupe l'herbe mouillée après la pluie — mais une fois à bord du 'Cornwall’, ils comprenaient vite leur erreur.\nOn en pouvait plus de supporter ça, "+pchar.lastname+". Certains ont même rédigé des requêtes pour des mutations – mais elles disparaissaient sur les étagères de l'Amirauté ou dans ses fourneaux. Pourtant, la vie nous a tout de même donné une chance : ce n'est pas nous qu'on a transférés du 'Cornwall’, mais quelqu'un d'autre – sur lui. John Lawson – le chouchou de Cromwell, tu en as sûrement entendu parler.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Il savait déjà lécher les bottes à l'époque — et peut-être qu'il se serait bien entendu avec Casper, mais je ne l'ai pas laissé faire. J'ai piégé le petit Johnny, et un Joshua furieux, sans comprendre ce qui se passait, l'a tabassé à coups de canne.";
			link.l1 = "Un vrai déshonneur pour un officier. Et Lawson a tout raconté à mon père ?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Bien sûr. Mais tu vois, le système ne peut pas se bouffer lui-même. L'affaire n'a jamais été rendue publique — on a proposé à Lawson une promotion anticipée, et Joshua, avec le 'Cornwall’, a été mis au placard — on nous a transférés de Londres à Plymouth, dans le sud de l'Angleterre. On aurait bien continué à faire peur à vous autres, bouffeurs de grenouilles, mais le 'Cornwall' a été transformé en navire de ravitaillement, transportant du matériel militaire à Dundalk, un petit patelin en Irlande.";
			link.l1 = "Et c'est là que vous avez rencontré Thérèse ?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "Dès notre première escale là-bas. Thérèse O'Fatt, comme je l'ai déjà dit, était serveuse dans une taverne locale. Trois jours ont suffi pour qu'on comprenne — on était faits l'un pour l'autre. Je pense que toi aussi tu peux comprendre ça, "+pchar.lastname+", hein ?";
			link.l1 = "On dirait bien, ouais, hein ?";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "En vous regardant maintenant, on ne dirait pas que vous connaissez le mot 'amour'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Je n'ai jamais rencontré personne de plus belle – ni avant, ni pendant les vingt années qui ont suivi. J'ai sans doute été, pour la première fois de ma vie, vraiment heureux, et elle aussi – du moins, c'est ce qu'elle disait.";
			link.l1 = "Et vous lui avez proposé de partir avec vous ?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Je n'ai jamais rencontré personne de plus belle – ni avant, ni pendant les vingt années qui ont suivi. Sans doute, pour la première fois de ma vie, je me suis senti vraiment heureux, et elle aussi – du moins, c'est ce qu'elle affirmait.";
			link.l1 = "Et tu lui as proposé de partir avec toi ?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Bien sûr que non – c'était impossible, puisque le 'Cornwall' restait un navire de guerre avec ce salaud de capitaine à sa tête. Après une semaine qui nous a semblé une éternité, notre brick est reparti pour Plymouth. Nous sommes revenus à Dundalk deux mois plus tard – et Teresa m'a assommée avec une nouvelle : elle était enceinte.";
			link.l1 = "Ouais, ça arrive, quand tu mets une fille au lit.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Fais pas le malin, grenouille. Thérèse pleurait sur mon épaule, pendant que je me demandais quoi faire. Je voulais rester avec elle, vraiment — mais je sentais déjà que cet enfant n'apporterait rien de bon.\nJ'ai essayé de convaincre Thérèse de s'en débarrasser, tant qu'il était encore temps — mais ça n'a fait qu'aggraver sa crise. On n'a pas su quoi faire — alors on a décidé d'attendre deux mois de plus, jusqu'au prochain retour du 'Cornwall' à Dundalk, car à ce moment-là, l'Amirauté n'avait pas encore pardonné à Casper\nAfter our return I didn’t find her immediately — Theresa’s pregnancy had grown obvious, and, as the owner of the tavern where she worked told me, her scoundrel of a father beat her and locked her up in the house. Needless to say, I dealt with that scoundrel so severely that he nearly vomited his own guts. Obviously, there was no question of her continuing to live in that house.";
			link.l1 = "Et vous l'avez amenée sur le 'Cornwall' ?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Il fallait agir vite. Je savais que Casper n'accepterait jamais une femme à bord, et j'avais prévu, la nuit suivant notre départ, de voler une chaloupe pour rejoindre Dublin, qui devait se trouver justement sur notre tribord.";
			link.l1 = "Et qu'est-ce qui s'est passé ? On vous a attrapés ?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Exactement. Casper s'était déjà enfilé sa dose de whisky, alors il n'écoutait rien. Il a simplement ordonné de jeter la fille par-dessus bord. J'ai beau l'avoir supplié, il ne faisait que rire comme un fou — bordel, j'te raconte ça et j'ai encore son rire en tête...";
			link.l1 = "Et alors vous avez décidé de vous mutiner ?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Je n'avais pas le choix. J'ai arraché le pistolet de la ceinture d'un veilleur à côté de moi, et j'ai fait un trou dans le front de cet enfoiré. Un massacre a éclaté aussitôt — personne n'aimait le capitaine, mais la peur du tribunal était plus forte. Ça a coûté la vie à près d'un tiers de l'équipage — quand on a enfin repris nos esprits, tout le pont du 'Cornwall' baignait dans le sang et les corps de nos camarades.";
			link.l1 = "Après ça, vous avez évidemment décidé de ne pas retourner en Angleterre. Là-bas, c'est la corde qui vous attendrait, hein ?";
			link.l1.go = "WildRose_Rupert_40";
		break;

		case "WildRose_Rupert_40":
			dialog.text = "J’étais certain que je pourrais conduire 'Cornwell' à travers l’océan. Ici, nos visages étaient inconnus, et cela nous donnait l’occasion de commencer une nouvelle vie. Convaincre les autres officiers n’a pas été difficile — ce n’était pas tant mon autorité que le contenu de quelques coffres, que les simples matelots ignoraient. L’équipage a décidé que Joshua Kasper devait rester en vie. Nous, les officiers de montagne, avons décidé de gagner du temps, sacrifier un des coffres et accoster à Antigua, où je prendrais son nom. Ensuite, nous avions l’intention de mettre le cap sur Providence.\n Et voilà : personne ne soupçonna la substitution. Mais quand il ne restait que quelques jours jusqu’à Providence, un salaud parla du second coffre — et cela provoqua une rupture au sein de l’équipage.";
			link.l1 = "Ils ont donc fomenté une mutinerie contre vous ?";
			link.l1.go = "WildRose_Rupert_45";
		break;


		case "WildRose_Rupert_45":
			dialog.text = "Non, mais le nombre de ceux qui voulaient continuer à servir notre glorieux roi a brusquement diminué. Ceux qui étaient prêts à devenir pirates n'étaient pas nombreux non plus. Alors on a trouvé une solution intermédiaire : on a décidé de jeter l'ancre dans l'un des ports français. Là, on comptait vendre le navire, partager l'argent obtenu pour lui et celui qui était dans le coffre, puis chacun partirait de son côté.";
			link.l1 = "Et ça ne vous dérangeait pas de devoir vivre parmi ces catholiques que vous détestez tant ?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Je me fichais bien de l'endroit où accoster : Thérèse, même si elle faisait bonne figure, se sentait exactement comme n'importe quelle femme enceinte après trois mois de roulis constant. Et, comme trois mois plus tôt, je n'avais rien contre la compagnie des catholiques — tant que je pouvais rester près d'elle.";
			link.l1 = "Mais il n'y a pas, et il n'y a jamais eu, de colonies françaises dans le nord-ouest de la mer des Caraïbes.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "Au moment où la situation à bord du 'Cornwall' a atteint son paroxysme, nous avions déjà parcouru la moitié du chemin avec un vent favorable, qui ne nous permettait plus désormais de mettre le cap sur Saint-Christophe...";
			link.l1 = "Et vous avez choisi Tortuga comme destination ?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "À cette époque, ce n'était encore qu'un simple village. Pour retarder d'éventuelles poursuites des autorités, on a changé la plaque du nom à l'arrière du brick – c'est ainsi que le 'Cornwall' est devenu le 'Wrangler’.";
			link.l1 = "Mais pourtant, vous n'êtes jamais arrivés jusqu'à la Tortue. Vous ne pouviez quand même pas vous tromper de cap au point de vous retrouver à l'ouest de Cuba au lieu de la Tortue ?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Je te signale que je suis une navigatrice chevronnée – bien meilleure que beaucoup d'autres. Il n'y a eu aucune erreur, on tenait le cap plein nord. Mais dès qu'on est entrés dans le détroit au Vent, une tempête effroyable s'est abattue sur nous. Je me demande encore par quel miracle on ne s'est pas écrasés sur la côte cubaine, mais qu'on a été entraînés le long d'elle, hein ?..";
			link.l1 = "C'est un vrai miracle, pas autrement.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "En serrant contre moi Thérèse en larmes, je suppliais ardemment le Seigneur de nous envoyer le salut. Et Il nous a vraiment donné un sacré coup de main.";
			link.l1 = "Vous avez échoué sur l'Île de la Justice.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "La justice — oh oui ! Le 'Wrangler' s'est brisé en deux contre le récif, mais il a miraculeusement gardé assez de flottabilité pour dériver jusqu'à d'autres navires empilés les uns sur les autres. La tempête a encore fait rage pendant presque deux jours, et quand elle s'est enfin calmée — les habitants de cette pauvre île nous ont secourus.";
			link.l1 = "Vous, Thérèse et deux autres matelots. Nous avons une idée de ce qui s'est passé ensuite. Racontez-nous plutôt comment vous vous êtes échappés de la prison et avez quitté l'île.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "J'aurais préféré qu'ils m'abattent sur-le-champ... Si j'avais su ce qui m'attendait, je me serais enchaîné moi-même aux barreaux sans jamais bouger.";
			link.l1 = "Le tartan était-il vraiment moins confortable que la goélette, ouais, hein ? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Ne me dites pas que vous vous êtes retrouvés dans la tempête en plus à bord d'une tartane.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Une tartane ? Ha-ha-ha... Ouais, c'était ça, mon plan. J'pensais avoir de la chance. Le chef de la prison était un ancien officier de la flotte anglaise, touché par mon histoire. C'est lui qui m'a parlé des tartanes des contrebandiers cubains — et du fait qu'on prévoyait de m'exécuter. C'était sans doute un homme d'honneur — c'est lui qui m'a proposé de me libérer, pour que je confie mon sort au destin.";
			link.l1 = "Je ne comprends pas... Si ce n'était pas sur des tartanes, alors comment avez-vous quitté l'île ?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;


		case "WildRose_Rupert_64_2":
			dialog.text = "La tartane ? Ha-ha-ha... Ouais, hein, c'était bien mon plan. J'ai cru que j'avais de la chance. Le chef de la garde de la prison était un ancien officier de la flotte anglaise, qui a été touché par ma détresse. C'est lui qui m'a parlé des tartanes des contrebandiers cubains, et aussi du fait qu'on prévoyait de m'exécuter. On pourrait sans doute l'appeler un homme d'honneur – c'est lui-même qui m'a proposé de me libérer, pour que je me remette au destin.";
			link.l1 = "Je ne comprends pas... Si ce n'était pas sur des tartanes, alors comment avez-vous quitté l'île ?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Si tu fermes ta gueule et que t'écoutes, tu comprendras. Je nageais vers les tartanes, longtemps — jusqu'à ce que, à travers le rideau de pluie, j'aperçoive une lumière. C'était quelque chose d'absolument incroyable, bordel. Elle brillait comme le soleil, sur le pont d'un des galions à moitié coulés, et je me suis dirigé vers elle. Sans savoir encore que j'étais en train de faire la pire erreur de toute ma vie. Je suis monté à bord par l'échelle de flanc — et je me suis retrouvé face à cette lumière. Elle scintillait au-dessus d'une statue dorée, et...";
			link.l1 = "L'idole de Kukulkan. Ouais, à cette époque-là, le 'San Jeronimo' n'avait pas encore sombré...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Alors, toi aussi tu l'as vu, "+pchar.lastname+"?";
			link.l1 = "Pas seulement vu. Je me suis déplacé dans l'espace grâce à lui, et ce, plusieurs fois.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Tu mens ! Plusieurs fois, tu dis ?! Comment tu peux être là, devant moi, en pleine forme alors ?!";
			link.l1 = "Après avoir été déplacé, j'ai bu une potion indienne, c'est ça qui m'a aidé à survivre et à reprendre des forces.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, c'est donc ça. Tu sais combien de temps il m'a fallu pour reprendre des forces ? Tu le sais ?!";
			link.l1 = "Je suppose. Vous avez touché à l'idole, et elle vous a transporté à la Dominique — près du village indien, là on vous a sacrifié à la statue et vous vous êtes retrouvé sur le Main, c'est ça ?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Exactement. Jamais je n'ai souffert autant que ce jour-là, étendu près de cette statue. Je ne saurais même pas à quoi comparer cette douleur. Même si une maison en pierre s'effondrait sur toi — tu ne souffrirais pas autant. À peine revenu à moi, j'ai vu une nouvelle foule d'autochtones s'approcher. Si j'avais parlé leur langue — je te jure que je les aurais suppliés de me tuer sur-le-champ.";
			link.l1 = "C'étaient les Indiens Miskitos du village d'à côté ?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Ce sont eux. Ils m'ont traînée dans une des cabanes, où un indigène étrange, qui ne leur ressemblait pas, m'a versé quelque chose directement dans la bouche. La douleur s'est un peu calmée, mais elle n'est pas complètement passée. Le soir, ils m'ont sortie près du feu, et ce vaurien tout peinturluré a commencé à faire un genre de rituel. Pauvre salaud.";
			link.l1 = "Œil-de-Serpent... Vous auriez dû lui être reconnaissant de vous avoir sauvé la peau.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Sauvetage ?.. Trois ans, "+pchar.lastname+". Pendant trois ans, je suis resté presque sans bouger, à faire mes besoins et à pisser sous moi, à me réveiller dans mon propre vomi – parce que je ne supportais plus toutes ces décoctions et teintures infectes qu'on me forçait à avaler ! Et puis il m'a encore fallu presque un an pour réapprendre à marcher.";
			link.l1 = "Une histoire bouleversante. Mais franchement, je vous plains, vous savez.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Va fourrer ta pitié à ton Pape dans son gros cul catholique. Je n'ai pas besoin de la pitié de qui que ce soit. Je continue, ou tu veux du temps pour pleurnicher, petit coq ?";
			link.l1 = "Ce voyage ne vous a certainement pas rendu plus poli. Mais bon, pour Mary, je vais supporter. Même si, je pense, on a déjà appris l'essentiel – écoutons-vous jusqu'au bout, quand même.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Je me suis relevé tant bien que mal, j'ai quitté ce village maudit et j'ai atteint la côte, jusqu'à la baie d'Amatique. Là, j'ai croisé des contrebandiers dont le navire avait jeté l'ancre non loin, et je me suis joint à eux en me faisant appeler Rupert Casper — je n'ai pas renoncé à mon prénom, mais j'ai gardé aussi le nom de l'un des responsables de tous mes malheurs. Pour ne jamais oublier pourquoi je me suis retrouvé là.";
			link.l1 = "Tout le monde est coupable à part vous, Northwood... Sauf vous-même, bien sûr. Enfin, on peut comprendre — des années d'humiliations et de souffrances, et maintenant vous voilà coincé dans ces bois. Comment ne pas perdre la tête, hein ?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Vous en avez vu, des choses, Northwood – c'est indéniable. Et vous voilà… Dans les bois, au bout du monde. On ne devient pas fou, ici…";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Je suis le maître de ces bois, "+pchar.lastname+" . En un peu plus de quinze ans, j'ai fait mon chemin d'un pauvre matelot sur un navire de contrebandiers jusqu'à devenir leur chef. Pas le capitaine d'un simple bateau, non – le maître de toute la côte, de la baie d'Amatique jusqu'au golfe de la Perdition.";
			link.l1 = "Eh bien, une renaissance digne de ce nom, je l'admets.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Je suis le maître de ces bois, "+pchar.lastname+" . En plus de quinze ans, j'ai fait mon chemin d'un pauvre matelot sur un navire de contrebandiers jusqu'à devenir leur chef. Pas le capitaine d'un petit bateau quelconque – mais le maître de toute la côte, de la baie d'Amatique jusqu'au golfe de la Perdition.";
			link.l1 = "Eh bien, une renaissance digne de ce nom, je l'admets.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Certains disent que c'est le domaine du Diable des Bois... Un mensonge éhonté — c'est mon territoire. Et Svenson le sait, ha-ha-ha. Il a envoyé ses hommes ici plus d'une fois, a essayé de découvrir qui je suis — aucun n'est jamais revenu. Du moins pas vivant, hé-hé. On peut compter sur les doigts d'une main ceux qui savent sous quel nom j'ai commencé ma carrière de contrebandier — et où je vis dans ces bois.";
			link.l1 = "Donc, maintenant vous vous faites appeler autrement. Voilà pourquoi la nouvelle que quelqu'un cherche Rupert Casper vous a mis dans un tel état de panique.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "La panique ? Tu es sérieux, mec ? Le seul qui panique ici, c'est toi – sur mon territoire, entouré de mes hommes, complètement à ma merci ! Je peux faire de toi tout ce que je veux. Et d'elle aussi – rien que parce qu'elle est la cause de toutes ces épreuves que j'ai traversées !";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Tu es fou, complètement fou, ouais. Je ne connais ni remède ni médecin qui pourrait te guérir, Rupert Northwood ! Tu as traversé des épreuves terribles, mais… comment peux-tu tout me reprocher à moi ?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Je t'ai déjà dit : sans toi, rien de tout ça ne serait arrivé. Reconnais-le, c'est tout.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Laisse-le, "+npchar.name+" . On en a entendu assez. Il y a vraiment des chemins qu'il vaut mieux ne pas parcourir jusqu'au bout. J'avais un mauvais pressentiment quand on a décidé de se lancer là-dedans. Mais je ne l'ai pas écouté. Dommage.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Ouais, hein, alors vous ne seriez pas tous les deux coincés ici, impuissants à faire quoi que ce soit. Ressens donc maintenant dans ta propre chair, ma fille, ce que j'ai enduré !";
			link.l1 = "Et qui t'a dit qu'on était impuissants à faire quoi que ce soit ? Équi-i-i-pe, en avant !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "Qu'est-ce qu'il y a, bleu ? T'as perdu quelqu'un ? Ha-ha-ha… Ha-ha-ha. HA-HA-HA-HA-HA-HA !!! Oh là là, si tu voyais ta tête, idiot ! Hé, Mason, amène ici mon cadeau pour nos invités.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Salopard ! Où sont mes hommes ?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Tu parles de cette poignée d'imbéciles qui ont cru bon de me tendre une embuscade ? Mon ami le tavernier m'a prévenu à temps de ton arrivée en ville, et je les ai accueillis comme il se doit... Quelques-uns ont réussi à se faire la malle. Mais t'inquiète pas — j'en ai attrapé un vivant. Pour que tu voies de tes propres yeux quel sort vous attend aujourd'hui.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Canaille ! Tu vas payer pour ça ! (pleure) Je te le jure, ouais, hein !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso ! Comme je suis contente de te voir !";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "Et moi donc, capitaine, quel plaisir de vous voir ! Quelqu'un a soufflé à ce salopard que vous étiez à sa recherche — et on s'est pris une volée de mitraille en pleine route. Avec une poignée de gars, on a réussi à battre en retraite, et on a foncé au port pour donner l'alerte. Heureusement, le veilleur en poste, dès qu'il m'a vu arriver sur la barque que j'avais achetée à la va-vite en ville, a tout de suite compris. Il a rassemblé des hommes — et nous voilà, venus vous tirer de là.";
			link.l1 = "Merci à toi, mon ami. Tu nous as sauvés d'une mort certaine.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Des broutilles. Qu'est-ce qu'on fait maintenant, cap'taine ?";
			link.l1 = "Rassemble les gens et allez sur le navire. Mary et moi, on a besoin d'être seuls.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Mon Dieu, "+pchar.name+"... Je n'arrive toujours pas, je n'arrive tout simplement pas à y croire. Mon père... C'est un monstre... Pourquoi il me fait ça ? Est-ce qu'il est vraiment devenu fou ?";
			link.l1 = "Il a dû endurer des souffrances terribles. La mutinerie sur le 'Cornwall', la fuite à travers l'Atlantique, la tempête et la mort de ta mère. Je n'imagine même pas comment il a survécu au passage des portails de ces idoles sans la potion des Comanches – mais c'est justement ça qui a détruit sa raison.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "Et si c'était déjà comme ça avant ? Ou bien, s'il était un vaurien, mais un peu moins, et qu'il aimait vraiment ma mère ? Peut-être que tout ça n'a fait que libérer ce qu'il avait au fond de lui ? Et si c'est le cas… et si moi aussi, j'ai quelque chose de lui ? C'est possible, non ? "+pchar.name+", ouais, hein ?";
			link.l1 = "Tu as clairement hérité de quelque chose de lui, "+npchar.name+". Dans le combat d’aujourd’hui, je l’ai vu — tu te bats avec la même détermination, le même feu dans les yeux, la même fureur que lui. Mais tu n’as pas sa folie. Tu es différente. Vivante, ouverte, le cœur à nu. C’est pour ça que je t’aime. Et il semble bien que Northwood avait raison : tu tiens de ta mère, pour ce qui est du caractère.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Tu le penses vraiment, mon chéri ?";
			link.l1 = "Bien sûr, ma chérie. Si je l'avais rencontré comme ça, sans savoir qui il était, jamais je n'aurais pensé que vous étiez de la même famille.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Tu sais, sur l'Île de la Justice, il n'y a pas tant de distractions que ça. Depuis toute petite, j'ai adoré l'escrime – au début, je me battais avec des garçons, avec des bâtons en bois, et puis après, avec des hommes, avec de vraies lames, ouais, hein ? J'ai toujours voulu être leur égale… mais j'avais l'impression d'être plus faible, même quand je gagnais.\nAlors je rentrais simplement chez moi – et je recommençais à m'exercer. Je m'entraînais pendant des heures, jusqu'à ce que mes bras se mettent à trembler, ouais, hein ? C'est ça, ce fameux feu ? Cette rage dont tu parles ?";
			link.l1 = "D'une certaine façon, ouais. J'ai l'impression que ce feu te donne bien plus de force que tu ne le crois toi-même. Et, que tu le veuilles ou non, c'est un don de ton père. Même s'il n'avait pas l'intention de t'offrir quoi que ce soit.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Tu crois qu'on a bien fait de remuer le passé, ouais, hein ?";
			link.l1 = "Maintenant qu'on sait tout… ça n'a plus vraiment l'air d'une si bonne idée. Mais si tu veux connaître la vérité, faut être prêt à ce qu'elle ne te plaise pas, ouais, hein ?";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Tu as raison, "+pchar.name+", ouais... Restons encore un peu ici. Je n'ai pas envie de retourner sur le navire tout de suite. J'ai juste envie de... rester là, dans le silence.";
			link.l1 = "Bien sûr, ma chérie. J'allais justement te le proposer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", arriver à temps, capitaine "+pchar.name+".";
			link.l1 = "Je savais que je pouvais compter sur toi, mon ami. Merci — personne n’aurait pu faire mieux.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "La jungle est la maison de "+npchar.name+". "+npchar.name+" content de se battre dans la jungle. La jungle donne force à "+npchar.name+".";
			link.l1 = "C’est exactement pour ça que je t’ai envoyé diriger l’escouade. Et j’ai bien fait — comme tu vois, on nous attendait ici à bras ouverts.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "Qu’est-ce que le capitaine "+pchar.name+" compte faire maintenant ?";
			link.l1 = "Mary et moi avons besoin d’un moment à deux. Rassemble les blessés et conduis-les au navire, prenez aussi les morts — nous les confierons à la mer. Et, "+npchar.name+"... dis à Alonso que le père de Mary doit être enterré comme il se doit, selon les rites protestants, quelque part ici. Lui seul et toi devez savoir où. N’en parle à personne, pas même à Mary. Elle n’a pas besoin de raviver ces souvenirs.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+" comprendre, capitaine "+pchar.name+". Tichingitu faire tout.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Des sales types, solides... Mais on les a bien eus, ha ha. Qu’ils pourrissent ici à se demander si ça valait le coup de s’en prendre à nous.";
			link.l1 = "Merci, "+npchar.name+", excellent travail. Je n’ose imaginer ce qui serait arrivé à Mary... et à moi... si je ne vous avais pas envoyés couvrir nos arrières...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ha, cap’, tu t’en serais sorti, je te connais. T’as vu la machette de leur chef ? J’ai pas lâché son regard. Si elle te plaît pas, je serais pas vexé si tu me l’offrais.";
			link.l1 = "Hmm... On verra, mon pote, on verra. Pour l’instant, rassemble ceux qui ont survécu et retournez au navire. Prenez aussi les morts — on les confiera à la mer. Et... ce chef — c’était le père de Mary. Prends Alonso et enterrez-le selon les rites protestants, quelque part ici. Que personne ne sache où se trouve la tombe. Surtout pas Mary. Elle n’a pas besoin de raviver ces souvenirs.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Ce sera fait, cap’. Attends... Enfin, non... J’y vais.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Il faisait chaud ici, cap’. Ces salopards ont eu ce qu’ils méritaient. T’as vu la tête de ce nabot quand on est arrivés ?";
			link.l1 = "Il ne s’attendait clairement pas à ça. Tout comme Mary et moi ne nous attendions pas à ce que ce soit un tel salaud. Mais bon, j’ai bien fait de suivre mon instinct en décidant de couvrir nos arrières.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "T’es pas un nouveau dans les Caraïbes. T’as dû t’habituer à toute la racaille qui traîne ici, au point de sentir l’embrouille avec ton cul. Alors, qu’est-ce qu’on fait ? On retourne au navire ?";
			link.l1 = "Récupère les blessés, les morts aussi, et remontez à bord. Ceux qui sont tombés, on les confiera à la mer, comme les fils fidèles qu’ils étaient. Mary et moi on viendra après — on a besoin d’un moment à nous. Et encore une chose : enterrez le père de Mary selon le rite protestant. Tu peux demander de l’aide à Alonso. Mais veille à ce que personne ne sache où est la tombe. Surtout pas Mary. Elle n’a pas besoin de raviver ces souvenirs.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "T’as raison. Elle n’a rien à faire ici à pleurer sur une tombe. T’inquiète, on fera tout comme il faut — et personne n’en saura rien.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Capitaine, monsieur, rapport : l’embuscade a fonctionné, les vauriens sont morts, le capitaine est sain et sauf.";
			link.l1 = "Tu crois que c’est le moment de faire de l’esprit ? Mauvaise idée. Tu veux frotter le pont devant les matelots ? Ils se fendraient bien la poire... Je te conseille de ne plus tester ma patience. Surtout aujourd’hui.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Euh... en fait, je suis officier, et...";
			link.l1 = "Pour l’instant. Aujourd’hui officier — demain mousse, et après-demain mendiant.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Compris : " + GetFullName(pchar) + " est le capitaine sérieux. Fini les blagues. Vos ordres, monsieur ?";
			link.l1 = "Rassemble les blessés et emmène-les au navire. Dis à Alonso de prendre une équipe et de récupérer les corps de nos gars — on les remettra à la mer. Qu’il enterre aussi le père de Mary selon les traditions protestantes. Lui seul et celui qui l’aide doivent savoir où se trouve la tombe. Mary ne doit rien savoir. Je ne veux pas qu’elle se torture avec ça.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Très bien... Ce sera fait. Et t’en fais pas, je sais tenir ma langue.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Monsieur le capitaine, nous avons gagné. Pas un seul chien ne s’est échappé.";
			link.l1 = "Beau travail, "+npchar.name+", merci. Je savais que je pouvais compter sur toi. Rassemble tous les survivants et retournez au navire. Mary et moi resterons un moment à terre.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "Et pour les corps des morts, que devons-nous faire ?";
			link.l1 = "Nous les confierons à la mer. Dis à Alonso de s’occuper de la préparation des corps. Et dis-lui aussi que le père de Mary doit être enterré selon les traditions protestantes, ici, dans la jungle, loin des regards. Personne ne doit savoir où est la tombe — surtout pas Mary. La connaissant, elle voudrait revenir ici, et cela ne lui ferait aucun bien.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Je transmettrai tout. Autre chose, capitaine ?";
			link.l1 = "C’est tout, mon ami. Va te reposer et soigne tes blessures.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Quel carnage... Ça va, cap’ ?";
			link.l1 = "J’irais bien... si Mary et moi n’avions pas dû tuer son père...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "On dirait bien que c’était un sacré salopard...";
			link.l1 = "Là-dessus, tu as raison, "+npchar.name+". Mais quoi qu’il ait fait, il doit être enterré dignement — selon les rites protestants. Tu t’en charges toi-même. Personne ne doit savoir où est cette tombe. Surtout pas Mary.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "Tu veux l’épargner de mauvais souvenirs ?";
			link.l1 = "Et de tourments inutiles. Envoie les autres au navire pour soigner leurs blessures. Ramenez aussi les morts à bord — on leur rendra hommage en mer, dès que Mary et moi reviendrons. Pour l’instant, on a besoin d’un moment seul à seul.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "Je dirai aux gars de ne pas venir vous chercher.";
			link.l1 = "Merci, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
} 
