void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...et du Saint-Esprit. Amen.";
			link.l1 = "Je vois rarement des militaires dans les églises.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Beaucoup croient que la foi et l'épée sont incompatibles. Mais un chirurgien ne coupe-t-il pas pour guérir? Un père ne punit-il pas pour protéger?";
			link.l1 = "On dirait une justification.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Il y a de la sagesse là-dedans. Parfois, la cruauté est nécessaire.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Tu te trompes. Ce n'est pas une justification - c'est une compréhension. Quand j'ai commencé mon service, chaque mort était... difficile. Mais ensuite... mes yeux se sont ouverts. 'La cruauté est la manifestation de l'amour suprême.'";
			link.l1 = "Je te laisse à tes prières.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Oui... oui ! C'est exactement ce qu'il a dit, celui qui m'a guidé sur ce chemin. 'La pitié sans force est inutile, comme une épée sans main.'";
			link.l1 = "Je te laisse à tes prières.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Priez pour nous tous. Pour ce que nous faisons... et ce que nous devons encore faire.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Sept pour cent de déficit. La dernière fois, c'était cinq. Ils poussent comme de la mauvaise herbe dans un jardin abandonné...";
			link.l1 = "Y a-t-il un nouveau gouverneur en ville ?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Quoi ? Ah, non. Son Excellence est là, dans le coin. Je suis don Fernando de Alamida, inspecteur royal.";
			link.l1 = "Ce doit être un travail difficile.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Tu sais ce qui est le plus difficile dans la lutte contre la corruption ? Les coupables ne sont pas forcément de mauvaises personnes. Ils ont des enfants, des familles. Et chaque fois, tu dois te rappeler : le poison reste du poison, même servi dans une coupe en or.";
			link.l1 = "Mais peut-on juger si sévèrement ? Nous sommes tous humains...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Tu es trop clément. Seule la prison les réformera.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "La misericorde envers le loup est cruauté envers les moutons. Ainsi parlait... un homme sage. Et chaque jour qui passe, je comprends de plus en plus sa sagesse.";
			link.l1 = "Je ne te distrairai plus de ton travail.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hum. Tu sais, je pensais de la même manière. Mais la prison, c'est trop simple. Il faut quelque chose de plus... Une purification.";
			link.l1 = "Je ne vais plus te distraire de ton travail.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Oui. Les papiers n'attendront pas. Bien que parfois, il me semble que derriere chaque chiffre ici se cache le destin de quelqu'un.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "J'écoute attentivement, "+GetAddress_Form(NPChar)+"? Qu'est-ce qui vous a poussé à m'aborder ainsi, dans la rue ?";
			link.l1 = "Tu te démarques des autres.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, inspecteur royal. Vous êtes le premier curieux de la journée. Tout le monde se cache, tout le monde me craint. Pourtant, une personne honnête n'a rien à craindre. Que cela nous dit-il ?";
			link.l1 = "Que ta réputation les effraie ?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Que les gens honnêtes sont rares ?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Amusant. Je l'ai pensé aussi. Jusqu'à ce que je comprenne - la peur purifie. Quand une personne a peur, elle devient plus honnête. Plus proche de sa vraie nature. De Dieu.";
			link.l1 = "Pensée intéressante. Je dois partir. Bonne journée, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Intéressant... Tu raisonnes comme quelqu'un que je connaissais. Dommage que tout le monde ne puisse accepter cette vérité.";
			link.l1 = "Pensée intéressante. Je dois y aller. Bonne journée, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Bon? Oui, peut-être. Tant que c'est juste.";
			link.l1 = "... ";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Autre chose, Capitaine ?";
			link.l1 = "Non, don Fernando, je dis juste bonjour, rien de plus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Une demoiselle avec une épée ? Eh bien, je n'aurais jamais cru vivre assez longtemps pour voir un tel spectacle. Et qui pourriez-vous être, señorita, pour oser attaquer le 'Sainte Miséricorde' ?";
				link.l1 = "Capitaine Helen McArthur. Et cette expression de surprise sur ton visage est bien connue pour moi.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Comment osez-vous ?! Attaquer le 'Sainte Misericorde' ?! Un navire qui porte la volonté du roi et... Eh bien. Puisque vous êtes là, dites-moi - pourquoi ? Pourquoi avez-vous choisi cette folie ?";
				link.l1 = "Je suis un pirate. Et ton galion est sûrement plein de trésors.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Un si beau navire... Je dois le posseder.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Je suis un ennemi de votre pays, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Juste parce que. Pourquoi pas ?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Comme vous ressemblez a la Vierge Marie, protectrice de notre navire... Tout aussi belle. Mais Elle protege les justes, tandis que vous...";
			link.l1 = "Je suis venu pour ton navire. Et les compliments ne serviront à rien ici, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Quel dommage. Je vais devoir t'apprendre l'humilité alors. Par la force, puisqu'il n'y a pas d'autre moyen.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah oui. Bien sûr. L'or. Toujours l'or. Le poison qui ronge les âmes. Pour lui, tu périras.";
			link.l1 = "Ne sois pas si dramatique. C'est juste des affaires.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Chaque piece dans la cale est le paiement des pecheurs pour la purification. Tu la veux? Alors partage leur destin.";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Beaucoup ont convoité la 'Sainte Miséricorde'. Sa beauté a été la perte de nombreux capitaines.";
			link.l1 = "Alors je serai le premier à le revendiquer.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "La misericorde sans force est inutile, comme une epee sans main. Cette leçon tu apprendras aujourd'hui.";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Alors c'est ça. Encore un jaloux de la grandeur de l'Empire.";
			link.l1 = "Quelle grandeur ? Tes manières rigides freinent ce monde.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Ne te mens pas à toi-même. La peur de l'Espagne te rend plus honnête. Plus proche de ta véritable nature. Tu verras par toi-même maintenant.";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Fou. Ou peut-être as-tu été envoyé à moi comme une épreuve ?";
			link.l1 = "Tout n'a pas besoin d'une raison, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Il a dit que les gens comme toi sont les plus dangereux. Mais cela ne fera que renforcer ma main au combat.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Une telle force d'esprit... Une telle volonté...";
				link.l1 = "Surpris ?";
			}
			else
			{
				dialog.text = "Pas mal. Cela fait un moment que je n'ai pas rencontré un adversaire digne.";
				link.l1 = "Je ne te laisserai pas le temps de te reposer.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "On m'avait averti... d'une telle épreuve. D'une beauté qui pourrait ébranler la foi d'un guerrier.";
				link.l1 = "Complices-tu toujours les choses simples à ce point, don Fernando ?";
			}
			else
			{
				dialog.text = "Le Seigneur donne de la force à ceux qui servent une cause juste. Mais... parfois je ne suis plus sûr de ce que je sers.";
				link.l1 = "Avez-vous des doutes ?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Simple ? Non... Il doit y avoir un sens plus profond. C'est une épreuve. Je ne peux pas me tromper.";
			}
			else
			{
				dialog.text = "Non. Il m'a appris à ne pas douter. Jamais.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Attends... Attends. Tu as gagné. Je suis blessé, je saigne. Permets-moi de prier avant la mort.";
			link.l1 = "Très bien.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Seigneur... pardonne-moi mes péchés et donne-moi la force en cette heure d'épreuve. Bénis les âmes de mes camarades tombés. Fidèles marins, ils sont morts en croyant qu'ils portaient la justice\nPère, j'ai essayé de vivre selon tes enseignements, de combattre l'injustice. Mais ton fils a entaché l'honneur de la famille Alamida. Pardonne-moi\nPatrie... J'ai juré de te servir fidèlement et véritablement. Mais mon ardeur, ma colère... Je suis devenu ce que je cherchais à combattre\nDiego... Peut-être a-t-il menti ? Tout ce temps... Malheur à moi si c'est le cas\nEt bénis cette femme, Seigneur. Peut-être dans ta miséricorde finale l'as-tu envoyée à moi... pour que je puisse voir à quel point je m'étais égaré. Amen.";
			}
			else
			{
				dialog.text = "Seigneur... pardonne-moi mes péchés et donne-moi la force en cette heure d'épreuve. Bénis les âmes de mes camarades tombés. Fidèles marins, ils sont morts en croyant qu'ils portaient la justice\nPère, j'ai essayé de vivre selon tes enseignements, de combattre l'injustice. Mais ton fils a terni l'honneur de la famille Alamida. Pardonne-moi\nPatrie... J'ai juré de te servir fidèlement et sincèrement. Mais mon ardeur, ma colère... Je suis devenu ce contre quoi je cherchais à lutter\nDiego... Peut-être a-t-il menti ? Tout ce temps... Malheur à moi si c'est le cas\nSainte Vierge Marie, prie Dieu pour nous et accorde-nous ta miséricorde. Amen.";
			}
			link.l1 = "Je ne vous reconnais pas, don Fernando. Vous semblez être une personne différente maintenant. Et de qui parliez-vous ?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Mon capitaine, félicitations ! Quelle bataille féroce. Ce capitaine était habile, oh si habile. Mais vous... vous vous êtes montré encore meilleur. Comme je suis fier de vous...";
			link.l1 = "Merci, mon amour. Es-tu blessé ?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Non, non. Bien que je pensais que nous étions au bord du gouffre à plusieurs reprises - avant l'abordage et pendant. Et toi, ça va ?";
			link.l1 = "Je vais bien, merci encore. Va te reposer dans la cabine, je te rejoindrai bientôt.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, es-tu d'accord ? Je suis venu aussi vite que j'ai pu, d'accord.";
			link.l1 = "Je vais bien, merci, cher. Bien que ce fut tout un combat.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Je suis content ! Mais... Écoute, Charles ? Pourquoi avons-nous attaqué ces gens ? Le Seigneur ne nous pardonnera pas cela, non. Ce navire... comme un grand temple. Quand je l'ai vu, mon cœur a tremblé, tout comme lorsque j'ai vu une véritable église pour la première fois, pas seulement dans les livres. Et maintenant il saigne !";
			link.l1 = "Mary... Tu sais que les apparences peuvent etre trompeuses. Et derriere le masque de la piete, il y avait ceux qui prenaient de l'argent aux simples croyants - tout comme toi. Comprends-tu?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Je... je te crois, Charles. D'accord. Seulement... donnons au moins une partie de l'or que nous avons trouvé ici à ceux qui en ont vraiment besoin ? Cela apaiserait mon cœur.";
			link.l1 = "On fera cela, Mary. Je te le promets. Maintenant, reprends tes esprits et essaie de te calmer. Tout est fini.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha, eh bien, félicitations pour votre victoire, capitaine ! Voilà ce que j'appelle du commerce ! Quelle prise sur ce galion !..";
			link.l1 = "Ton sourire est encore plus large que d'habitude aujourd'hui, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Tu paries! De tels butins. Et quel combat. Cela m'a rappelé la Révolution. Et aussi... héhé.";
			link.l1 = "Qu'est-ce que c'est, Tommy ? Allez, parle.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Ils ont aménagé tout le navire comme une cathédrale flottante. Et amassé tant d'or de partout. De vrais fanatiques papistes ! Honteux et risible.";
			link.l1 = "C'est un navire-trésor, Tommy. Pas un navire d'église.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Pas grande différence dans notre cas. Quoi qu'il en soit, j'étais ravi d'apprendre à ces dons et papistes une bonne leçon ! Je ne peux pas supporter ni l'un ni l'autre. J'ai vraiment apprécié cette journée, ha-ha-ha !";
			link.l1 = "Tu ne changes jamais ! D'accord, congé. Tout est sous contrôle ici.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Capitaine Charles, nous avons remporté la victoire. Ce fut un combat difficile. Même Tichingitu a trouvé cela ardu, et je suis l'un des meilleurs guerriers du village.";
				link.l1 = "Vrai, mon ami. Ils étaient en vérité des adversaires dignes.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, le navire est à nous.";
				link.l1 = "Très bien, Tichingitu. J'ai juste fini ici aussi.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Capitaine Paterson, dernière résistance écrasée sur le navire.";
				link.l1 = "Tu es en retard, Tich ! La prochaine fois, reste mieux avec moi. Pas que je n'aurais pas pu le gérer seul, note bien...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Capitaine McArthur, vous allez bien ?";
				link.l1 = "Oui, Tichingitu, je vais bien, merci de t'en inquiéter. Et cesse de douter de ton capitaine - je m'en suis parfaitement bien sorti tout seul.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Les esprits me le disent pendant le combat. Et demandent pourquoi moi les tuer. Maintenant moi te demande la même chose. Tichingitu voit dans leurs yeux, ils ne sont pas des méchants. Pas encore.";
				link.l1 = "Ah, que puis-je te dire ? Je n'ai pas de réponse, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Moi vouloir te poser question, Capitaine de Montoya.";
				link.l1 = "Je vous écoute.";
			}
			if (startHeroType == 3)
			{
				dialog.text = " Tichingitu veut vous poser une question, Capitaine William, si vous le permettez.";
				link.l1 = "Accordé.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Moi pas douter, moi m'inquiéter pour toi, capitaine.";
				link.l1 = "D'accord, d'accord. Je vois dans tes yeux que tu veux me demander autre chose.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, comme vous dites, capitaine. Nous avons fini ici ?";
				link.l1 = "Oui. Je vais encore jeter un oeil, puis rejoindre les autres.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Ces gens-là, ils ne sont pas de la même tribu que toi ? Ils ne sont pas espagnols ? Pourquoi as-tu décidé d'attaquer ?";
				link.l1 = "C'est vrai. Mais les tribus indiennes ne se battent-elles pas aussi entre elles? Ou n'y a-t-il pas de querelles et de disputes au sein d'une même tribu?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Ce navire ressemble à une église. Tu hais l'église et le dieu blanc ?";
				link.l1 = "Pas du tout. Mais c'est juste de la décoration, voyez-vous ? C'est un navire trésor. Bien que vous ne comprendriez pas - j'ai entendu dire que votre peuple ne sait même pas ce que sont les impôts. Sacrés veinards.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Oui. Sois honnête. Capitaine MacArthur, pourquoi attaquons-nous cette église flottante ?";
				link.l1 = "Église flottante, ha-ha-ha ! Non, non. C'est un navire de trésor. Hmm, je vois que tu ne comprends pas tout à fait. Eh bien, ils transportaient de l'or. J'imagine combien Jan sera fier quand je lui dirai que j'ai vaincu Fernando de Alamida !";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, tu as raison, capitaine. Mais avec les Indiens, cela arrive moins souvent qu'avec l'homme blanc.";
				link.l1 = "Peut-être. Eh bien, cet homme... se mêlait de mes affaires.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Sois sincère, Maskogi n'ont ni châteaux ni taxes.";
				link.l1 = "Exactement. Tu peux y aller, tu es en retard de toute façon. Plus tard, nous déciderons quoi faire de ce beau galion. Je n'aime pas ces barcasses, mais bon sang, elle est magnifique.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu aussi fier de vous, capitaine. Et vous félicite pour la victoire dans ce combat difficile.";
				link.l1 = "Merci.  Maintenant, partageons le butin.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Vous vous mêlez de cela, Señor de Montoya ?";
			link.l1 = "Exactement. Cet Archipel est trop petit pour nous deux. Et je suis bien plus utile à notre état ici. Souviens-toi de Feuille de Cacao - il a fait plus de mal que de bien à ses frères. Pareil ici.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Maintenant, moi comprendre. Tichingitu peut partir, capitaine ?";
			link.l1 = "Oui, vas-y. Je vous rejoindrai bientôt aussi.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Eh, c'est quoi cette histoire de brandir des armes ? Range ça tout de suite !","Je vous ordonne de ranger votre arme sur-le-champ !","Eh bien, "+GetAddress_Form(NPChar)+", arrête de faire peur aux gens! Range ton arme.");
			link.l1 = LinkRandPhrase("D'accord, je vais le ranger...","Déjà fait.","Comme tu dis...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Va te faire foutre !","Je suppose que je vais l'utiliser !","Je le rangerai quand le moment sera venu.");
			link.l2.go = "fight";
		break;
		
	}
} 