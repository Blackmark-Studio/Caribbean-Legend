// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "Que veux-tu?";
			link.l1 = "Je devrais y aller...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Capitaine Charles de Maure ! Enfin ! Son Excellence Jacques Dille de Parkuet exige de vous voir ! C'est urgent !";
			link.l1 = "Pourquoi ne suis-je pas surpris ? Très bien, veuillez dire à Son Excellence que j'arrive bientôt.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "Mes yeux doivent me tromper si c'est Charles de Maure lui-même ! Je ne fais pas souvent de telles réceptions et je suis ravi que vous ayez trouvé un peu de temps à consacrer à mon humble cloître. Quelle chance ! Cela mérite un toast !";
			link.l1 = "Mes hommages, madame. Pardonnez-moi si mon comportement vous déçoit - cela fait très longtemps que je n'ai pas assisté à de tels... événements. L'étiquette à bord d'un navire se réduit à la subordination, des foulards propres et une tasse régulière de café rafraîchissant chaque matin.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Si charmant, Capitaine, vous avez toujours votre vernis parisien avec vous. Je peux voir son regard timide sous ce masque aguerri et salé. Ne vous inquiétez pas, je suis tellement heureux de vous rencontrer enfin que je peux vous pardonner beaucoup de choses. Pour l'instant. Nous verrons comment cela se passe entre nous à l'avenir. Du vin ? Rouge ou blanc ?";
			link.l1 = "Un moment parfait pour une blague sur le rhum, mais hélas, je ne suis pas d'humeur, je suis désolé. Je boirai volontiers tout ce que tes jolies mains me verseront.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Bien joué. Mais j'insiste. Le goût pour le vin peut en dire long sur un homme et j'ai l'intention d'apprendre tout sur vous ce soir. Alors je demande encore : rouge ou blanc ?";
			link.l1 = "A ta guise. Je vois que tu bois du rouge. Pareil pour moi - j'aimerais aussi en apprendre un peu plus sur toi.";
			link.l1.go = "Julianna_3";
			link.l2 = "Dans ce cas, je prendrai du blanc mais c'est toi qui choisis. Cela devrait fonctionner dans les deux sens, n'est-ce pas ?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Splendide, c'est donc mon tour maintenant ? Celui-ci est un Pinot Noir de Bourgogne, les vignerons l'appellent 'une fille espiègle'. Ce n'est pas une variété facile à manier et son arrière-goût peut être assez trompeur aussi. Satisfait ?";
			link.l1 = "Pinot Noir, hein ? Ça me va. Peu fiable et mystérieux, un goût sombre au début mais laissez-le respirer un moment et vous serez surpris. Une danse légère de nuances et de goûts, un choix de connaisseur avisé. Les premières impressions mentent, n'est-ce pas ? Je bois à vos yeux, madame !";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Splendide, alors c'est mon tour maintenant ? J'ai un merveilleux Sauvignon Blanc, directement de la vallée de la Loire. Assez sauvage, on peut presque sentir comment il éclate sur la langue. Et la cerise sur le gâteau - une note de poudre à canon. Je suppose que vous avez quelque chose en commun.";
			link.l1 = "Je m'attendais à mieux, peut-être quelque chose comme du Riesling. Eh bien, prenons ce simple rustre qui sent l'été et la poudre à canon. Avez-vous déjà entendu dire que certains le confondent avec du pipi de chat ? Je boirai à ton sourire, aussi éclatant que ces saphirs !";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Remarquable, Charles ! Puis-je t'appeler ainsi ? Je ne me suis pas trompé sur ton compte, un autre jour tu serais la vedette de ma nuit. Mais hélas, mon Capitaine, aujourd'hui tu as une forte concurrence. Il semble que nous sommes au bord d'un scandale là-bas, vois-tu ?";
			link.l1 = "J'entends des voix en colère. Qui est cet odieux monsieur et qu'a-t-il fait pour déplaire à notre cher gouverneur ?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Ce 'désagréable' monsieur est Angerran de Chievous, un bâtard non reconnu du Comte de Levi Vantadur. Vous êtes en train de divertir leur sujet de dispute. De Chievous essaie d'obtenir ma bonne grâce depuis des années, et il m'a suivi ici, pensant qu'il peut remplacer son père pour moi. Même s'il n'est pas un fils légitime, il est riche et puissant. L'entêtement est un autre de ses traits, pour certaines personnes il remplace la sagesse. Juste avant votre arrivée, lui et Jacques ont commencé à se disputer sur le sujet évident. Son Excellence me protège toujours d'une manière très touchante, vous devriez voir ! Allez, observons et voyons comment cela se termine cette fois.";
			link.l1 = "Je sens des ennuis dans l'air... Pourquoi y a-t-il toujours un piège, même en une nuit si merveilleuse...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Je vous demande pardon, Charles ?";
			link.l1 = "Oublie ça. Présente-moi ton ami insistant, puis nous verrons...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, permettez-moi de vous présenter mon cher invité - le Capitaine Charles de Maure, en chair et en os, nous a honorés de sa visite ! De telles figures célèbres ne sont pas souvent des invités ici.";
			link.l1 = "... ";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles,   je   n'aime   pas où cela mène ! Jacques est sourd à mes arguments tandis qu'Angerran prépare sûrement quelque chose. Ce combat avait un but et j'ai besoin de ton aide !";
			link.l1 = "J'ai bien peur de ne pas vous suivre... Que puis-je bien faire ici ? Il a déjà refusé de se battre en duel avec moi...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Capitaine, je vous en prie, ne me décevez pas. Il y a un instant, vous étiez un virtuose des conversations et maintenant votre monde est divisé entre les choses que vous pouvez transpercer avec une épée et celles que vous ne pouvez pas. Pensez hors des sentiers battus ! Gâchons la pièce d'Angerran. Il veut défier le pauvre Jacques tout seul, mais c'est juste ennuyeux ! Organisons un tournoi ! Plusieurs gentilshommes ici peuvent soutenir des enjeux sérieux et votre chance est déjà connue comme légendaire ! Peut-être que les cartes vous favoriseront ce soir ?";
			link.l1 = "Je ne vois pas vraiment comment cela empêchera de Chievous de se battre avec notre doux gouverneur, mais je suis partant, ma dame. Tout pour effacer ce petit sourire de son visage.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Splendide, maintenant va à la table et prends quelque chose à manger, ce sera une longue nuit. Une fois prêt, retrouve-moi dans la salle, nous aurons besoin de plus de place pour cela. En attendant, je vais offrir un spectacle, persuadant les autres de me donner des lunettes et des jeux à enjeux élevés. Je pourrais même leur crier dessus pour que ces coqs remarquent une dame s'ennuyant à mourir. S'il te plaît, n'interviens pas, personne ne doit savoir que nous sommes dans la même équipe ce soir. À plus tard, mon Capitaine !";
			link.l1 = "Tout ce que vous dites, madame, tout ce que vous dites...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Eh bien, félicitez-moi, ça a marché! Un peu d'orgueil, quelques préjugés et voilà! Faites une tête ennuyée, ils nous regardent. Qu'ils pensent que vous êtes intéressé par la boisson, pas par moi\nUn tournoi est sur le point de commencer, les enjeux sont élevés, pas de seconde chance ni de revanche. D'une certaine manière, je sais que vous êtes habitué à cela. Vous vous en sortirez. Souvenez-vous, Angerran prépare certainement quelque chose, il va agir contre notre ami Jacques, mais il n'a pas pris en compte votre arrivée. Soyez mon atout dans la manche, car voir son visage arrogant et confiant n'est jamais bon signe. Nous avons huit joueurs mais j'ai fait en sorte que vous ne le rencontriez qu'en finale\nOh! Votre premier adversaire! Colonel et Commandant de notre fort. La mer contre la terre - un défi digne pour des invités avec une expérience militaire! Applaudissements!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Tu as fait un excellent travail, Charles, vraiment splendide. Angerran et Jacques vont bientôt s'affronter. Dommage qu'ils n'aient pas écouté et repoussé le tournoi d'une semaine. J'aurais pu rassembler une compagnie vraiment brillante dont les ragots auraient voyagé jusqu'à Paris ! Eh bien, peut-être la prochaine fois. Il semble que ton prochain adversaire soit un concurrent digne de ta chance, un vrai loup de mer, le Capitaine Moreno ! Capitaines, s'il vous plaît !";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Hélas, la chance vous a abandonné, Capitaine. Je suis désolé, mais la partie est terminée pour vous. Angerran joue déjà contre Jacques, alors je dois y aller. Adieu.";
				link.l1 = "C'était un plaisir... madame.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Je vous félicite pour votre victoire bien méritée, Capitaine ! Il est encore incertain qui vous affrontera lors de notre finale... Retirons-nous un peu. Baissez la voix et observez cette table. Regardez, le voilà ! Je commence à comprendre ce qu'Angerran mijote ! Il a déjà dépouillé le doux Jacques de son argent, mais il ne le laisse pas quitter la table. Quand je suis passé, le pauvre bougre pariait sur des documents pour un navire entier avec une cargaison. Malheureusement, la chance n'est pas de son côté ce soir. Ou quelqu'un lui a dit de ne pas l'être.";
				link.l1 = "Tu penses que de Chievous triche ?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Hélas, votre chance vous a fait défaut, Capitaine. Je suis désolé, mais la partie est terminée pour vous. Angerran joue déjà contre Jacques, alors je devrais y aller. Adieu.";
				link.l1 = "C'était un plaisir... madame.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Il le pourrait certainement s'il le voulait mais je n'ai aucune preuve. Notre cher gouverneur est bon aux cartes, mais son adversaire l'est aussi. Angerran n'a même pas cillé quand il a parié sur sa frégate, imagine cela. Si nous avions ce duel à Paris ou à Lyon, cela deviendrait une légende, Charles ! Néanmoins, il pourrait juste avoir de la chance ce soir. Approchons-nous d'eux et voyons par nous-mêmes.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, tiens-moi ou je vais tomber... Ou je ne tomberai pas - ces idiots ne remarqueront même pas que je fais semblant. As-tu vu cela ? Jacques, maudit soit ta stupidité ! Comme un enfant, Jésus ! Un enfant imbécile !";
			link.l1 = "Marquise, je ne pense pas vous comprendre. Que se passe-t-il à cette table maintenant ? Sur quoi parient-ils ?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Sur moi, Charles. Notre doux et stupide Jacques a parié sur moi. Angerran a trouvé son seul point faible et l'a frappé au bon moment.";
			link.l1 = "Tonnerre de Brest ! Mais je suis le prochain dans le tournoi, je pourrais regagner son fichu navire en jouant ! Pourquoi ?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Parce qu'Angerran y avait beaucoup réfléchi et avait tout planifié. Écoute-moi, nous n'avons pas beaucoup de temps. Tu dois lui faire la même chose. Dépouille-le de tout, prends tout son argent, tous ses navires, provoque-le ! Fais-lui perdre la tête sur la réputation, l'honneur, la passion, sur n'importe quoi ! Tu as vu comment cela se fait ce soir. Accule-le et force-le à miser. Je te supplie, Charles ! Je suis prêt à tout, mais je n'irai pas vers lui. Pas comme ça ! Même le Comte Vantadur ne s'opposera pas à une victoire de cartes honnête, il ne lèvera même pas le petit doigt pour m'aider. Tu vois, les cartes sont sacrément sacrées pour les nobles, qu'ils aillent au diable ! Tu es mon dernier et seul espoir, Charles !";
			link.l1 = "Ne mettez pas encore notre gouverneur en terre, madame. Peut-être qu'il regagnera son navire ? Dame Fortune est une femme... capricieuse.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Tu ne comprends toujours pas, n'est-ce pas ? La chance n'a pas sa place à cette table ! Angerran de Chievous tient les rênes. Il a découvert un moyen de m'avoir tout en tenant son père à l'écart. Je n'ai aucune idée de combien de temps il a planifié cela, mais il a presque gagné maintenant. Il maîtrise le jeu et nous n'avons qu'une seule chance de le briser. Tiens, prends ça ! Je vais faire semblant, cela te donnera une minute ou deux. Utilise-la judicieusement.";
			link.l1 = "Marquise... Quelqu'un, je vous en prie, aidez-moi ! Madame ne se sent pas bien ! Vite !";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Non, non, je vais bien... C'est un peu étouffant ici... Je suis désolé, messieurs. Je vais vous laisser pour prendre un peu d'air frais un instant. Vous pouvez continuer sans moi.";
			link.l1 = "... ";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Pas en ce moment et pas à St. Pierre mais je connais quelqu'un. Je te promets, Angerran, ce sera une peinture digne...";
			link.l1 = "... ";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, tu es impossible ! Apprends à perdre ! Ce n'est qu'un jeu et tu ne peux pas tout prévoir. Finis ton vin et habille-toi - les règles restent - un vaincu quitte notre joyeuse assemblée.";
			link.l1 = "Marquise, attendez...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "Cela va trop loin, messieurs ! Arrêtez ça immédiatement ! Nous sommes tous très fatigués après cette nuit épuisante et je crains de devoir demander à mes invités de prendre congé. Vous pourrez poursuivre votre dispute demain comme il sied à des hommes d'honneur, à moins que vous ne changiez d'avis. Mais personne ne touche aux armes ici, est-ce clair ?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, j'ai bien peur de devoir vous demander de prendre congé aussi. Montez à l'étage et prenez une chambre pour vous. Je m'occuperai de tout. Je suis reconnaissant pour tout ce que vous avez fait pour moi au-delà de toute mesure, mais j'ai besoin de temps pour moi-même et vous devez être terriblement fatigué.";
			link.l1 = "Ce n'est pas trop mal, madame, mais je ne dirai pas non à un lit. Cette fête informelle m'a frappé plus fort qu'une énorme escadre navale ennemie. Je comprends que tout cela n'a pas été facile pour vous non plus, marquise. Reposez-vous et ne vous inquiétez pas, vous ne me devez rien. Tout ce dont j'ai besoin maintenant, c'est de dormir.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Je m'assurerai qu'ils te réveillent à midi. Il est déjà l'aube, donc je ne peux plus te souhaiter bonne nuit. Dors bien.";
			link.l1 = "Vous aussi, marquise.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Te voilà, Charles. À vrai dire, je n'ai pas dormi du tout, mais tu as l'air bien reposé. Comment as-tu dormi ? Le petit-déjeuner est en route.";
			link.l1 = "Votre hospitalité est légendaire, madame, mais je crains de n'avoir pas le temps d'en profiter. Son Excellence, les seconds de de Chievous, les navires que j'ai gagnés - tout cela m'attend.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Tu n'as pas seulement gagné les navires. C'est une autre chose dont je voulais te parler, Charles...";
			link.l1 = "Je ne suis ni Jacques ni Angerran, marquise. Je ne joue pas aux cartes pour gagner la faveur des femmes. Vous ne me devez rien.";
			link.l1.go = "Julianna_41";
			link.l2 = "Vous êtes sous ma protection, marquise. Ni Jacques, ni Angerran ne vous importuneront jamais, je peux vous le promettre.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Tu es soit fabuleusement honorable, soit amoureux, Charles. Et pas de moi. Mais encore une fois, je te suis éternellement reconnaissante de tout coeur. Si je peux t'aider en quoi que ce soit - dis-le moi simplement.";
			link.l1 = "Julianne, le temps presse et je fais face à la tâche la plus ardue qui soit. De Chievous est une ordure et même un duel honnête peut rapidement se terminer comme celui que nous avons observé la nuit dernière. Parlons plus tard quand tout cela sera terminé pour de bon. Je vous remercie pour la chance de dormir en silence et j'ai hâte de vous revoir.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Je te suis reconnaissante de tout coeur, Charles... Crois-moi, être ton trophée est aussi une sorte de victoire pour moi. Disons que toi et moi devrions continuer cette conversation dans un environnement plus... intime ?";
			link.l1 = "Julianne, le temps presse et je fais face à la tâche la plus malaisée qui soit. De Chievous est une ordure et même un duel honnête peut rapidement se terminer comme celui que nous avons observé la nuit dernière. Parlons plus tard quand tout cela sera réglé une bonne fois pour toutes. Je vous remercie pour l'opportunité de dormir en silence et j'ai hâte de vous revoir.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Je ne vous retarderai plus alors, mon Capitaine. Cependant, souvenez-vous, Angerran est dangereux. Je ne peux juger de ses capacités de combat, mais il a participé à plusieurs guerres et combattu à Rocroi. J'ai aussi entendu parler de quelques duels qu'il a gagnés, principalement au pistolet. Par-dessus tout, c'est un type fourbe, comme vous l'avez vous-même remarqué. Je vous en prie, soyez prudent et venez me voir après, je vous en conjure !";
			link.l1 = "Le souci vous sied à merveille, marquise. Croyez-moi, de Chievous n'est pas le premier salaud à se dresser sur mon chemin. Je saurai m'en débrouiller. À présent, je devrais vraiment aller voir Son Excellence et discuter de l'affaire du duel.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Bon vent, mon Capitaine ! Et dis à Jacques de se tenir aussi loin que possible des portes de ma maison.";
			link.l1 = "Vous avez ma parole. À bientôt, marquise !";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Capitaine, vous y êtes parvenu, quel soulagement ! Comment cela s'est-il passé ? Saignez-vous ?!";
			link.l1 = "Ce n'est pas mon sang... du moins pas tout. Marquise, où est de Chievous ?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "J'allais te poser exactement la même question - tu ne l'as pas abattu ? Que s'est-il passé ? Pourquoi est-ce que je vois la moitié des gardes de la ville dehors ?";
			link.l1 = "J'ai dit au gouverneur que tu pourrais être en danger. De Chievous a été blessé et s'est enfui, lâchant ses brutes sur nous. Ce fut un massacre. Cependant, des histoires comme celle-ci ne sont pas pour tes belles oreilles. C'est fini. Tu es libre de lui et de notre 'cher' Jacques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "C'est si mauvais, Charles. Des ennemis comme Angerran de Chievous devraient être tués pour de bon quand tu en as l'occasion. J'ai connu cet homme pendant de nombreuses années - il n'est pas du genre à pardonner. Tôt ou tard, il trouvera le moyen de se venger. Mais je n'aime pas comment tu te tiens avachi, ta blessure a-t-elle été soignée ?";
			link.l1 = "Juste une égratignure, ça a été bien pire. Ça fait un peu mal, c'est tout. Merci de vous soucier de moi, madame, mais je devrais y aller...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Capitaine, vous avez joué pour moi, risquant vos navires et votre richesse, vous vous êtes battu pour moi dans un marché, risquant votre vie et votre carrière. Le moins que je puisse faire pour vous est de soigner vos blessures et de vous offrir un endroit où vous reposer en sécurité. Non ! Je ne veux plus entendre parler de cela. Prenez ma main et suivez-moi à l'étage. Votre chambre vous attend.";
			link.l1 = "J'accepte votre offre, madame, merci. Mais je préfère ne pas vous accabler. Je monterai à l'étage moi-même.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marquise, vous êtes mon ange gardien. J'ai peur que ce soit moi qui vous doive maintenant.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, tu es un exemple de chevalerie ! Je jure devant Dieu, si tu continues ainsi, je vais perdre la tête ! D'accord, mon chevalier, je t'enverrai Denise, elle prendra soin de tes blessures comme tout bon médecin le ferait.";
			link.l1 = "Merci, marquise. Si mon coeur n'était déjà pris, je jouerais volontiers le jeu. Mais hélas ! Bonne nuit !";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "Dans ce cas, j'exige que tu me fasses plaisir immédiatement. Prends ma main et fais ce que je dis. Denise ! Apporte-moi de la charpie, du vin chaud et quelque chose à manger à l'étage ! Allons-y, mon Capitaine. Et rappelle-toi - pas de disputes cette fois !";
			link.l1 = "Comme vous dites, marquise, je suis tout à vous.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Bonjour, Charles. Comment vont ces 'égratignures' à toi?";
				link.l1 = "Grâce à vos efforts, je me sens renaître. Veuillez accepter ma sincère gratitude, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Bonjour, mon héros. Comment vont ces 'égratignures' à toi ?";
				link.l1 = "Merci pour votre sollicitude, madame, je vais tout à fait bien. Je paierais une fortune pour que votre Denise serve comme médecin de mon navire. Elle est un miracle !";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Je crains que cela ne soit pas facile à arranger. Mais je n'oserais jamais vous réveiller sans une raison sérieuse. Croyez-moi, j'ai veillé sur votre sommeil sans peur, mais cet homme en bas est très insistant. Il dit qu'il fait partie de votre équipage et que c'est urgent.";
			link.l1 = "Mon équipage ? Vous avez bien fait de me réveiller, marquise ! Je vais partir immédiatement.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "Dans des circonstances différentes, je le ferais, mon capitaine, mais nous devrons reporter. Un monsieur extrêmement peu éduqué vous attend en bas. Il dit qu'il fait partie de votre équipage et que c'est urgent.";
			link.l1 = "Nous y reviendrons, Madame, quand je serai de retour. J'espère que ce n'est pas à propos des Espagnols qui assiègent à nouveau.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, tu es de retour ! Quelles nouvelles t'a apportées ton homme ? Tu n'as même pas dit au revoir !";
			link.l1 = "Je m'excuse, marquise. De Chievous a encore joué un sale tour. Il a volé mon navire et a mis les voiles cette nuit. Un de mes officiers de confiance était sur ce navire et je ne peux pas la laisser entre les mains de ce salaud.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Elle ? Vous avez une femme officier à bord de votre navire ? Cela va à l'encontre de tout ce que je sais de la navigation. Qu'est-ce qui vous fait penser qu'elle est encore en vie ?";
			link.l1 = "J'espère. Julianna, l'espoir est tout ce que j'ai pour l'instant. Je dois en apprendre plus sur Angerran de Chievous. Je dois absolument découvrir où il est allé ! Je dois la ramener !";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Maintenant je vois ! Vous êtes en effet amoureux, mon chevalier ! Je donnerais volontiers la moitié de ma vie pour une telle loyauté et attachement sans y penser à deux fois !";
			link.l1 = "Je n'ai prêté aucun serment, mais cette femme compte beaucoup pour moi, marquise.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Ce jalousie est touchante. Ecoute cela, Charles, je suis prête à devenir jalouse à cause de toi ! Mais quelle courtisane peut rester sourde à la voix du véritable amour ? En plus, tu m'as sauvé, mon chevalier, bien sûr que je vais t'aider. Demande-moi ce que tu veux.";
			link.l1 = "Merci. Vous connaissez de Chievous depuis pas mal de temps. Où pourrait-il aller après tout ce remue-ménage pour attendre que la colère de son père passe ?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "Et si je pouvais te séduire avec un brunch? Tu n'as pas pensé à cette... fille pendant deux jours, peut-être peut-elle attendre un jour de plus?";
			link.l1 = "Marquise, je réalise comment je peux paraître à vos yeux, mais ce qui est fait est fait. Même si je n'ai prêté aucun serment, mon cœur lui appartient. Je vous supplie de me comprendre et de m'aider.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Allons, Charles ! Se defendre avec un discours d'amour devant une courtisane ? Je n'ai pas ri ainsi depuis longtemps ! Tu es tellement incroyable ! Détends-toi, ce qui s'est passé dans cette maison, reste dans cette maison. Je me souviens de ce que je te dois. Demande ce que tu veux.";
			link.l1 = "Merci. Vous connaissez de Chievous depuis pas mal de temps. Où pourrait-il se cacher après tout ce remue-ménage pour attendre que la colère de son père s'apaise ?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "La verité soit dite, même si inviter Angerran de Chievous n'est peut-être pas la chose la plus agréable à faire, c'est néanmoins très utile politiquement. Il est un invité bienvenu partout, y compris dans les nations alliées à la France. Mais je ne connais qu'un seul homme ici qui lui prêtera toujours la main et un sanctuaire. François de Lyon, le gouverneur de notre colonie de Guadeloupe. Il est un vieil associé du comte de Lévi Vantadur et a toujours eu un faible pour ce salaud.";
			link.l1 = "La Guadeloupe, donc! C’est la meilleure piste que je pouvais espérer! Si nous levons l’ancre ce soir, nous ne serons qu’à un jour derrière eux.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Attends, Charles, il y a autre chose. J'ai recu une lettre pour toi tout recemment. Je pensais que cela avait un rapport avec le duel, mais je n'en suis plus si sur. La voici.";
			link.l1 = "Pas de sceau, mais le papier est cher. Je n'aime pas ça...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Allez, Charles ! Ne me fais pas languir, est-ce de lui ?";
			link.l1 = "Oui, c'est de lui. Elle est vivante ! Il l'a capturée en volant mon navire. Maintenant, il propose que nous nous rencontrions et en discutions dans un environnement civilisé. Comme tu l'as dit, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monsieur de Lyons choisira certainement le fils de Leve Vantadur plutôt que toi. De Chievous pourrait te tendre un piège à nouveau ! Tu t'es fait un ennemi très puissant en me défendant, Charles. J'aimerais pouvoir t'aider, mais je crains que tout ce que je puisse faire, c'est te demander d'être prudent.";
			link.l1 = "Julianne, je n'aurais jamais survécu dans le Nouveau Monde si j'avais toujours choisi une approche directe. Les affaires louches ne sont pas mon domaine de prédilection, mais je sais m'y adapter.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Des nouvelles, capitaine ?";
			link.l1 = "Hélas, rien...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Content de te revoir, Charles ! Je suis heureux que tu sois sain et sauf. Quelles nouvelles ?";
			link.l1 = "Tout ce que nous savions des capacités de de Chievous s'est avéré être un grave euphémisme. Le salaud retient mon... officier captif, et je n'ai que deux semaines pour rassembler la rançon. Je crains que cela ne puisse se faire sans votre aide.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, ton amour est comme une anemone des vents, pourtant je te dois beaucoup et je t'aiderai du mieux que je peux. Comment puis-je te rendre service?";
			}
			else
			{
				dialog.text = "Charles, je t'ai déjà dit que je n'oublierai jamais ce que tu as fait pour moi. Je ferai ce que je peux pour te rembourser. Je suis prêt, mais je ne comprends pas bien comment je peux t'être utile dans cela ?";
			}
			link.l1 = "Veuillez vous asseoir, Julianna. Voyez, la rançon d'Angerran... c'est vous. Et je ne parle pas d'un parrainage officiel, je veux dire comme une captive ligotée dans sa cale.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Je suis sans voix... Mais ton visage me dit que ce n'est pas une plaisanterie. A-t-il perdu la tête ?";
			link.l1 = "Plutôt, il croit que je l'ai fait. Il est assez désespéré pour franchir toutes les limites possibles.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "Et quoi, vous me demandez ? De ne pas crier pendant mon enlèvement ? Capitaine, ne pensez-vous pas que c'est un peu trop demander ? Je vous dois beaucoup, mais sauver l'amour de quelqu'un d'autre en sacrifiant ma propre vie aux mains d'un bâtard sans gloire... Vous êtes la chevalerie ici tandis que je suis une femme extrêmement réaliste et matérialiste.";
			link.l1 = "Je crains, madame, que c'est exactement ce que je vous demande. Faites vos bagages, nous partons. Je suis profondément désolé pour cela mais le temps presse.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marquise, je ne kidnappe pas les femmes qui me font confiance. Et cela pourrait être notre chance.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Tu es plein de surprises, Charles. Tu as entendu ? C'était toute la grâce que j'avais pour toi, elle vient de se briser. Amour ou pas, je ne te laisserai pas m'enlever. Gardes ! A l'aide !!! Quelqu'un !!!!";
			link.l1 = "Et moi qui croyais que nous étions amis.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "C'est un scandale ! Qu'as-tu fait de mon salon ?! Quelle sorte d'horreur démoniaque est-ce ? Charles, reviens à la raison ! Tu es un gentilhomme, pas un maudit pirate !!";
			link.l1 = "Je vous ai déjà présenté mes excuses. Je vous ai demandé de ne pas compliquer les choses davantage - vous n'avez pas écouté. Croyez-moi, je n'aime pas ce que je fais, mais je n'ai pas le choix. Je ferai tout ce qu'il faut pour le bien de cette femme.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Quelle sorte de dame choisirait un chevalier tel que vous? J'irai moi-même, gardez vos mains loin de moi! Vous ne volez pas une vache, alors montrez un peu de dignité!";
			link.l1 = "Très bien. Venez avec moi, madame. Restez derrière moi et baissez la tête - peut-être qu'ils commenceront à tirer.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Un instant, j'ai cru ne pas te connaître du tout, Charles. Ce regard... Mais que vas-tu faire alors ? De quelle chance parlais-tu ?";
			link.l1 = "Pourquoi le salaud m'utilise-t-il pour t'atteindre ? Pourquoi a-t-il orchestré cette partie de cartes au lieu de simplement prendre ce qu'il voulait ? De quoi a-t-il peur ?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Rien. Hélas, mais les raisons derrière tout cela sont d'une primitive monotonie. Le comte Henri a toujours un faible pour moi. Angerran prendrait un grand risque s'il me faisait quoi que ce soit contre ma volonté. Je suis désolée Charles, mais c'est une impasse. Il niera tout et s'en sortira. Personne ne croira les paroles de toi, l'enleveur, tandis que son père te détruira.";
			link.l1 = "Sacrebleu ! J'aurais aimé que cela n'en arrive pas là... Préparez-vous, marquise, nous devons partir. Et oui, je vous demande de vous taire.";
			link.l1.go = "Julianna_76";
			link.l2 = "Mais le salaud doit avoir d'autres faiblesses à part son père, n'est-ce pas ? Il n'est pas parfait, bien au contraire, il est l'opposé du parfait !";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Je ne sais pas si cela nous sera utile... Angerran avait des affaires avec le baron pirate local. Jacques Baraban ?";
			link.l1 = "C'est Barbazon, madame. Un charmant couple, tous les deux ! Mais Jacques le Bon ne m'aime guère et je ne peux pas lancer une attaque sur Le Francois sans une certitude solide.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Vous êtes encore trop direct, mon chevalier. Vous vous souvenez du capitaine Moreno ? Votre deuxième adversaire de jeu ? Je parie qu'il est venu ici à cause d'Angerran. Il doit savoir quelque chose de valeur pour nous.";
				link.l1 = "Capitaine Moreno, hah ! Oui, bien sûr. Est-il toujours en ville ? Où puis-je le trouver ?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Tu es encore trop direct, mon chevalier. Quelqu'un sait toujours quelque chose et tout le monde ne peut pas garder la bouche fermée dans certaines situations. Mes... élèves entendent des choses, dans cette maison. Donne-moi un jour et j'en saurai plus ou je te trouverai quelqu'un qui le fera.";
				link.l1 = "Marquise, je pensais que l'inquiétude t'allait bien, mais la colère te va encore mieux. Merci, tu fais naître en moi l'espoir !";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Oui, il est toujours ici et je vous épargnerai de courir partout à sa recherche. Venez ici demain soir - le capitaine Moreno vous attendra ici, dans cette salle. J'aimerais pouvoir faire plus que cela, mais je ne peux pas, Charles.";
			link.l1 = "Il est déjà plus que suffisant, marquise. Avec lui à mes côtés, les choses seront beaucoup plus faciles. Merci. À demain soir.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "J'aurais aimé entendre cela de ta part dans une autre situation, Charles. Viens me voir demain soir. J'espère que j'obtiendrai ce dont tu as besoin.";
			link.l1 = "Merci encore, Julianna! Alors demain soir.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Te voici, mon ami ! Le capitaine Moreno t'attend déjà.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, je crois que j'ai trouvé quelque chose. Tu te souviens du capitaine Moreno? Celui qui a joué contre toi cette maudite nuit?";
				link.l1 = "Je le fais, quel vagabond. Que penses-tu de lui ?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Je l'ai toujours su, Bartolomeo de la Cueva. C'est pourquoi tu es venu à ma fête en premier lieu. C'était comme ajouter des piments à son dîner. Je sais que toi et tes gars avez déjà rôdé sur cette île depuis quelques semaines. Je sais que cela doit être lié d'une manière ou d'une autre au baron pirate de Le Francois et à Angerran de Chievous. Raconte tout à mon ami et nous garderons ton nom légendaire secret en échange. Sinon, j'appellerai les gardes qui se tiennent déjà derrière les portes. Je les ai appelés à ton arrivée.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Pas seulement eux ! Angerran m'a offert un collier, un magnifique ! De grandes et nettes perles, y compris celle-ci, sombre comme la nuit du sud, au milieu. Mais il l'a commandé chez les bijoutiers locaux !";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Je parie qu'il ne l'a pas fait juste pour me plaire avec un cadeau de luxe. Bien que, ce cadeau était son dernier recours pour obtenir ma faveur dans les limites de la décence. Angerran n'a ni titres ni terres, même sa frégate reste la sienne jusqu'à ce que son père en décide autrement. Il fait usage de pouvoir et d'influence mais il n'a pas de source de revenus propre. Peut-être qu'il en a eu assez d'attendre les dons de son père et a décidé de redresser sa situation financière ?";
			link.l1 = "Attendez, madame ! Le jeu de cartes ! Si nous avons raison, et que de Chievous a tout planifié à l'avance, il devait avoir besoin de beaucoup d'argent pour les enjeux afin de coincer notre gouverneur suffisamment. Demander une telle somme à un parent pourrait attirer une attention indésirable sur l'affaire. Voler des trésors déjà dérobés aux corsaires semble être un moyen discret et sûr d'obtenir la monnaie nécessaire. Personne ne saurait !";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "À nous, Charles ! Angerran ne doit pas s'en tirer à bon compte cette fois-ci. Sa position au-dessus de moi est allée trop loin et je voudrais vous aider à y remédier.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Un pirate perdant et une courtisane presque amoureuse. Charles, tu t'es fait une équipe de rêve !";
			link.l1 = "Néanmoins, merci à vous deux. Sincèrement ! Maintenant, je dois réfléchir un peu à cela et élaborer un plan.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Cette maison a tout ce que ses invités désirent. Je ferai les arrangements. Rejoins-nous quand tu seras prêt, Charles.";
			link.l1 = "Très bien, madame.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Rien, mais quelqu'un en ville le cherche. Ils s'enquièrent activement de vous et des autres invités de cette nuit-là. Je ne sais pas encore ce qui se passe, mais je suis sûr que vous êtes tombé sur quelque chose de plus grand que vous ne le pensez.";
			link.l1 = "Quelque chose de plus grand ? Que veux-tu dire, Julianne ?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... Je veux dire Monseniour de Chievous m'a offert un collier de perles magnifique en cadeau. L'une des perles était noire comme la nuit. Je pensais que ce n'était qu'un faux avec une belle histoire derrière. Je ne l'ai jamais porté, je ne voulais pas donner de faux espoirs, mais il est si envoûtantement beau.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Que feras-tu, Charles ? As-tu la moindre idee de ce qui se passe ?";
			link.l1 = "Pas encore, mais je le ferai. De Chievous est plongé jusqu'au cou dans quelque chose de sérieux et c'est ma chance. Sa patrie n'osera pas le toucher mais les autorités britanniques pourraient bien le faire. Je préférerais ne pas t'enlever, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "C'est très gentil de ta part, Charles, mais pas très drôle.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, as-tu appris quelque chose ? Tu as l'air nerveux... Qu'est-ce qui ne va pas ?";
			link.l1 = "Merde! Je souhaite que les choses soient différentes... Fais tes affaires, nous devrions partir, Marquise. Je t'en prie, ne fais pas d'histoires.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, entrez. Le baronnet est déjà ici et nous avons eu une conversation agréable. Je lui parlais justement de votre intérêt pour les événements en cours.";
			link.l1 = "Julianne, je ne suis pas si sûr que c'était sage...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, il semble que vos hommes viennent de laisser tomber quelque chose derrière la porte ! Auriez-vous l'amabilité de leur dire de se tenir mieux ?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Horrible ! Que faisons-nous maintenant ?!";
			link.l1 = "Bon sang ! Je souhaite que les choses soient différentes... Fais tes affaires, nous devrions partir, Marquise. Je t'en prie, ne cause pas de problèmes.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Dieu tout-puissant ! Qu'avez-vous fait de mon salon, messieurs ?! Cela ressemble à un cauchemar médiéval ! Qui sont ces gens ? Et où sont les gardes ?";
			link.l1 = "Tu vas bien, Julianne ? Bien. Je parie que les gardes dépensent leur pot-de-vin bien mérité dans une taverne. Baronnet, mes félicitations sont de mise - tu as réussi à mettre Goodman Jack sacrément en colère. Une tentative d'assassinat aussi désordonnée et mal préparée n'est pas du tout son style.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Je m'excuse d'interrompre votre discussion passionnante, mais à moins que l'un de vous ne soit blessé, passons dans un cabinet. Un spectacle comme celui-ci n'est guère réconfortant pour une dame... Seul le plafond est sans sang !";
			link.l1 = "Alors montez à l'étage, marquise. Vous devriez vraiment vous allonger un peu et vous éloigner de tout ce sang. Le baronnet Cortney et moi allons en discuter. Continuons-nous ?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, es-tu prêt à partager ton plan avec nous ?";
			link.l1 = "Presque. Dis-moi, de Chievous est-il du genre pedant? Tient-il ses livres et journaux en ordre?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran est l'incarnation de la lenteur quand il s'agit de finances ! Il signe plus de papier que n'importe quel banquier que je connais. Je suppose qu'il est comme ça depuis son enfance quand il ne savait pas qui était son père et vivait dans la pauvreté dans les rues.";
			link.l1 = "Splendide ! Maintenant, nous avons besoin de son journal de bord et de ses livres ! Ils feront une preuve viable pour les Britanniques. Nous devons découvrir comment les obtenir ! J'aurais aimé savoir cela quand j'avais son navire en ma possession... soupir.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Attends, Charles, crois-tu vraiment qu'après tout ce qui s'est passé, je vais me permettre de me vendre à de Chievous comme une chèvre de ferme ?";
			link.l1 = "Ne t'inquiète pas, Julianne, cela prendra juste quelques jours. Je te promets qu'ils te traiteront comme un vase précieux de Chine. Corrige-moi si je me trompe, mais de Chievous ne se montrera jamais à l'échange ?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "J'en suis sûr. Angerran attendra sous l'aile de Francois de Lyons et n'osera jamais te rencontrer en pleine mer. Mais à propos de cette capture...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, je suis désolé de te déranger, mais n'as-tu pas oublié de me demander mon avis sur tout cela ? Des semaines dans ces cercueils grinçants... Te rends-tu compte de ce que tu me demandes ?! Évidemment, tu es attaché à cette... fille, mais je ne suis pas l'un de tes matelots ! Je suis désolé, mais tout cela ne ressemble pas à une histoire d'amour sérieuse.";
				link.l1 = "Je crains, marquise, que je vais devoir insister. Je ne peux pas me permettre de la perdre.";
				link.l1.go = "Julianna_127";
				link.l2 = "Nous commettons tous des erreurs, Julianna. Toi plus que quiconque devrais le savoir. Je te demande de m'aider.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, je suis désolée d'interrompre, mais n'as-tu pas oublié de demander mon avis sur tout cela ? Des semaines dans ces cercueils grinçants... Réalises-tu seulement ce que tu me demandes ?! Tes sentiments sont dignes de la littérature classique sur la chevalerie, mais je ne suis qu'une simple courtisane. Je t'admire et je veux t'aider, mais tout a une limite !";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Je comprends, Charles. Je veux croire en l'amour véritable et parfait, mais je suppose qu'il n'y a rien de tel dans ce monde.";
				link.l1 = "Merci, marquise. Je vais tout arranger cette fois. J'ai beaucoup appris de cette histoire, et je prie pour ne pas payer un prix trop terrible pour ce que j'ai fait.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Tu as pris ta décision, je t'ai soutenu tout du long, mais trop c'est trop. Sacrifier tout pour l'amour que tu avais déjà abandonné dans ma chambre. Tout cela est très touchant, Charles, mais je ne suis pas si jeune et naïve.";
				link.l1 = "Je crains, marquise, que je devrai insister. Je ne peux pas me permettre de la perdre.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Eh bien, Capitaine, fais ce que tu veux. Je ne te résisterai pas, mais sache que je le fais contre ma volonté.";
			link.l1 = "Pense de moi ce que tu veux, Julianna, je l'ai mérité. Mais je la récupérerai, peu importe le prix\nJulianna, écoute, je sais ce que je te demande. De tout laisser derrière et de laisser les autres t'entraîner dans une entreprise douteuse. Mais en ce moment, tu es mon seul espoir ! J'ai besoin de ton aide pour cela et je te resterai redevable jusqu'à ma mort !";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Très bien, Capitaine. En fin de compte, Angerran doit être éliminé pour de bon. Je vais vous aider, mais dites-moi comment vous allez me sauver de son navire ?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Attendez. Vous pouvez prendre ma perle de collier, les Anglais chassent la perle noire, n'est-ce pas ? Celle-ci les fera vous écouter. Quelle est la suite ?";
			link.l1 = "Ensuite, je prendrai l'enquêteur à bord et nous naviguerons vers la Guadeloupe. Nous effectuerons une fouille officielle sur la frégate de Chievous lorsqu'elle reviendra avec vous à bord. L'affaire du Mercury était un incident grave impliquant notre allié, donc De Lyon devra le permettre !";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Il dira à tout le monde que ce sont ses hommes qui m'ont sauvé de la captivité. Et sachez, Capitaine, je n'ai pas encore décidé ce que je leur dirai.";
				link.l1 = "Ne rien dire serait bien, marquise. Croyez-moi, je vous sortirai d'ici et je ferai payer Angerran pour tout.";
			}
			else
			{
				dialog.text = "Je leur dirai que j'ai été enlevé par des étrangers, directement de chez moi, pour être mis à bord du navire d'Angerran. Cela semblera qu'il a payé des mercenaires pour me kidnapper.";
				link.l1 = "Un autre clou dans le cercueil d'Angerran, marquise.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Donne-moi du temps jusqu'au matin à moins que tu ne veuilles me transporter dans un sac. Envoie aussi quelques hommes pour m'aider - une femme de stature ne peut pas voyager sans commodités. Charles, tu m'as sauvé et je vais t'aider, prends aussi cette perle noire inestimable, mon cadeau pour toi. Si cela fonctionne, nous serons quittes.";
				link.l1 = "Comme vous le dites, marquise. Bon vent à vous deux ! On se revoit ici une fois que ce sera terminé.";
			}
			else
			{
				dialog.text = "Je serai prêt à partir au lever du soleil. Je ne vais pas me traîner dans une cale, alors assurez-vous de préparer une chambre décente, ou quoi que vous appeliez cela, pour moi. Charles, tiens, prends ceci. C'est une précieuse perle noire. Je me rends compte que cela vaut plus que cet endroit, mais certaines choses ne peuvent être mesurées en or. J'espère que cela te sera utile. Que Dieu te vienne en aide !";
				link.l1 = "Bon vent à vous deux ! Reviens ici une fois que ce sera terminé.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Félicitations, Capitaine. Votre plan a réussi. Quel scandale immense vous avez orchestré ! Les Anglais ont pris Angerran et son navire avec tout son contenu sauf moi.";
				link.l1 = "Sir William n'est même pas venu dire au revoir. Il a promis de s'excuser.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, nous l'avons fait ! Ils te libéreront à tout moment ! Nous devons quitter l'île au plus vite cependant. Le gouverneur est très contrarié par l'arrestation récente d'Angerran.";
				link.l1 = "Je suis ravi de te voir, Julianne. Comment vas-tu ? Comment s'est passé l'échange ? Est-elle en sécurité ?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Je suppose qu'il avait été trop occupé pour cela. Comme notre gouverneur en ce moment. Tu ferais mieux de quitter la ville avant qu'il ne se souvienne de ton existence. Il aimait bien le fils d'Henri, mais les papiers britanniques l'ont complètement acculé. Je n'attendrais pas qu'il décide de déverser toute sa frustration sur toi.";
			link.l1 = "Assez juste. De plus, elle m'attend en Martinique. Comment s'est passé l'échange ? Va-t-elle bien ?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Excusez-moi, mais je ne veux pas en parler. Demandez-lui plutôt. Adieu, Capitaine. Je rentrerai par mes propres moyens. J'ai besoin de prendre une pause de la mer - Francois est un hôte assez agréable quand il n'est pas embêté par des fonctionnaires britanniques ennuyeux.";
			link.l1 = "Je suis sincèrement désolé pour tout cela, Madame. Merci quand même pour votre coopération. Je suis heureux d'entendre que vous vous êtes fait un nouvel... ami.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Merci à toi aussi, Charles, d'avoir tenu parole. Trouve Bartholomew dans ma maison à St. Pierre. Adieu. Nous nous reverrons.";
			link.l1 = "Adieu, Julianne. Bon vent.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Je ne l'ai pas vue, mais Bartholomew l'a capturée vivante et en bonne santé. Cet Anglais a arrêté de Chievous et sa propriété juste sous le nez du gouverneur local - il n'a même pas dit un mot ! Miraculeux !";
			link.l1 = "Tu sais, ça s'est étonnamment bien passé, compte tenu du contexte de cette arrestation. Bien que, cela devrait encore se retourner contre moi plus tard. Peu importe ! Je dois partir pour la Martinique immédiatement, je dois la voir dès que possible !";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Sans doute, vous avez beaucoup à vous dire. Oh, Charles, je souhaite avoir un homme avec un tel feu dans les yeux à mes côtés. Dépêchons-nous, un bain chaud et des draps propres me manquent vraiment. Bartholomew nous attendra chez moi à St. Pierre.";
			link.l1 = "Oui, le romantisme des voyages en mer est surestimé. Vous aurez ma cabine, marquise, c'est le moins que je puisse faire. Allez, venez.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Tu as déjà fait pour moi tout ce que tu pouvais, Charles. Tu as fait croire à nouveau à une femme cynique.";
			link.l1 = "Moi aussi, Julianne. Moi aussi.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, je suis si heureux que tu sois venu ! Comment va ta dame ? Est-elle en bonne sante ?";
				link.l1 = "Tout va bien, grâce à vous, Julianne. Je voulais vous le dire à nouveau. Vous êtes une femme merveilleuse et je vous serai à jamais redevable pour tout votre courage et votre ingéniosité.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, je suis si heureux que tu sois venu ! Comment va ta donzelle ? Elle va bien ?";
				link.l1 = "Tout va bien, grâce à vous, Julianne. Je voulais vous le dire encore une fois. Vous êtes une femme merveilleuse et je vous serai éternellement redevable pour tout votre courage et votre ingéniosité.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Peut-être est-ce moi qui vous suis redevable. Après tout, vous m'avez sauvé de deux clients extrêmement embêtants. Je pense que je vous dois encore quelque chose. Demandez ce que vous voulez, Charles.";
			link.l1 = "Dans ce cas, j'ai une petite faveur à demander, ma dame. Vous pouvez faire quelque chose pour nous rendre quittes.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Je suis tout ouïe, mon Capitaine. Qu'est-ce que c'est ?";
			link.l1 = "Les gens font des erreurs, mais cela ne rend pas le monde mauvais. Souviens-toi de cela et sois heureuse, Julianne. Tu mérites d'être heureuse.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Je... Je vais essayer, Charles. Merci. Viendras-tu me rendre visite de temps en temps... comme un ami ? Tu seras toujours le bienvenu chez moi !";
			link.l1 = "Je l'apprécie, marquise. Adieu et souviens-toi de ce que tu m'as promis.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Pourtant apparemment pas assez merveilleux... mais je suis heureux que cela se soit bien terminé pour vous. Vous ne me devez rien, après ce que vous avez fait, je ne saurais vous remercier assez ! Venez me voir dès que vous êtes à terre. Vous serez toujours le bienvenu chez moi, en tant qu'ami !";
			link.l1 = "Merci, marquise. Je te souhaite tout le meilleur. Adieu !";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, mon ami, tu es si grossier - me rendre visite si rarement ! Tu m'as manqué, tu le sais ? Envie d'un peu de vin ? Je meurs d'envie d'écouter des histoires passionnantes de première main ! Et de tester ta fameuse fortune !";
			link.l1 = "Marquise, je voulais juste te saluer et m'assurer que tu vas bien.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "Et te voilà, mon ami ! Heureux de te revoir !";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Eh bien, la manière dont vous traitez mon ami ne me laisse pas le choix, monsieur. J'accepte votre défi. L'heure et le lieu ?";
			link.l1 = "  Ici et maintenant. Appelez les serviteurs, dites-leur d'apporter des bougies, un crépuscule douillet comme celui-ci ne fera pas l'affaire. Cet endroit doit être aussi lumineux que le jour !  ";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Mon ami, je t'en prie, ne le prends pas trop personnellement. Angerran est un sale type, c'est vrai, mais tu ne devrais pas lui tirer dessus. Laisse-moi m'en occuper.";
			link.l1 = "Vous en êtes sûr, Votre Excellence ? Il est aussi ivre que mon quartier-maître après une semaine à terre, mais il sait assurément manier son épée. Je peux discerner ces choses-là tout de suite.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Dieu m'en garde, Charles ! Je ne vais pas me battre en duel avec lui. Nous jouerons aux cartes, ce sont les armes des hommes civilisés. Je vais le plumer et te l'envoyer quémander un prêt pour un retour sûr au Québec.";
			link.l1 = "C'est un plan solide, d'accord. Mais si tu me demandes, je préférerais ce salaud mort, pas pauvre. Bon vent, Votre Excellence !";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Merde, Angerran, c'est impossible qu'il y ait un dix là ! Impossible !";
			link.l1 = "Etait-ce une accusation ? C'était votre affaire, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Ce n'était pas. Je suis juste... un peu surexcité et je m'excuse. C'était un accident et j'exige une chance pour une revanche ! Ce navire, je... dois le récupérer ! Ou au diable le jeu, dis-moi juste combien tu es prêt à me la vendre ? Donne le prix et je m'assurerai qu'il soit payé demain avant midi !";
			link.l1 = "Hélas, mais je crois de tout cœur qu'on ne peut racheter les butins du jeu. On ne peut que les regagner. La flûte est à moi maintenant et je n'ai aucune intention de la vendre. Je suis désolé que votre passion vous ait mis dans une telle situation, parfois nous devrions être plus réalistes quant à nos capacités... Peut-être avez-vous d'autres papiers de navire ?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Tu es une racaille, Angerran, et tu m'as coincé. Je crois pouvoir te proposer une mise que tu accepteras.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, tu es mon seul espoir, je te supplie de m'aider ! Cette flute et sa... cargaison ont déjà été vendues à la Compagnie hollandaise. Je dois leur remettre tous les documents demain. Je pensais rester ici toute la nuit, alors je les ai apportés avec moi. Je serai confronté à une situation désastreuse si l'affaire est annulée !";
			link.l1 = "Mais 'cher Jacques', ne penses-tu pas que la femme que tu as favorisée fait face à une situation encore plus désastreuse maintenant ? J'ai eu ma part de jeux de hasard et je comprends quelque chose comme parier sur un navire, même si ce n'est pas le tien. Mais parier sur une dame ?! Tu m'as vraiment surpris ! Et maintenant, tout ce qui t'importe, c'est le sort de ton marché ?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Ne me juge pas, Charles. Favoriser une ancienne amante d'un puissant comte et même tomber amoureux juste un peu n'est rien comparé à devoir un million de pesos à Peter Stuyvesant. Comment expliquer cela à son agent ? Imagine tous les dégâts à ma réputation !";
			link.l1 = "J'avais une dette similaire avant mais je n'avais absolument rien et pourtant je m'en suis bien sorti. Toi aussi, tu t'en sortiras. À plus tard, Jacques. Pas de promesses et je ne te demanderai même pas quel genre de cargaison vaut un million, que tu la garderais dans la flûte.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Te voilà, Charles. J’étais sur le point de t’envoyer chercher. De Chievous insiste pour un duel et rejette déjà toute chance de réconciliation. Tu as bien joué aux cartes, mais es-tu sûr de vouloir continuer ainsi ?";
			link.l1 = "J'ai l'étrange impression, Votre Excellence, que vous désiriez ce résultat depuis le début. Alors je dis oui. Cela doit être résolu une fois pour toutes. Qu'en est-il des conditions du duel ?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Vous êtes trop dans votre tête, mon ami. Certaines parties de notre monde ne tournent toujours pas autour de vous. Croyez-moi, je suis profondément déçu de la façon dont tout s'est déroulé la nuit dernière. Très profondément. Mais d'abord, discutons du sort de vos... gains.";
			link.l1 = "D'accord. Voulez-vous savoir comment rendre votre flûte ou comment va Madame Julianne ?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Je vois que tu as troqué ton ironie inappropriée pour du dépit ? Charles, nous sommes du même côté, n'oublie pas cela.";
			link.l1 = "Argument discutable, Votre Excellence. Pour le dire légèrement. Maintenant, par où commençons-nous : le navire ou la dame ?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "Le marché Stuyvesant bien sûr - son agent m'attend depuis ce matin et je suis à court d'excuses. J'ai besoin des papiers de la flute, Charles.";
			link.l1 = "D'accord. Elle est à vous. Je ne crois pas que de Chievous ait joué honnêtement, donc vous pouvez récupérer votre bien pour la moitié de son prix. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Je serais ravi de m'y plier. Tu as dit que le prix du navire était de 500 000 ? Ça me va.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Maintenant, cela fera quatre cent soixante mille pesos, taxes incluses. Marché conclu. 135 000.";
			link.l1 = "Écoute... Je commence à en avoir assez de discuter. Alors paye, prends tes documents et terminons-en.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Tu n'as pas pitié des vieux amis, n'est-ce pas Charles? Maintenant, avec toutes les taxes incluses...";
			link.l1 = "Les dettes de cartes et l'amitié n'ont rien en commun, Votre Excellence. Vous payerez les taxes vous-même en tant qu'acheteur ou je vends le navire à Le Francois. Sachez que je ne profite pas de votre position... encore.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Très bien, soit. Maintenant, le duel. Je n'ai pas besoin d'ennuis avec le comte de Levi Vantadur, donc tout doit se passer aussi légalement que possible. M'avez-vous entendu, Charles ? Selon la loi ! Je vais envoyer deux officiers de ma garnison pour vous accompagner - ce sont deux hommes nobles et respectés. Ils seront vos témoins à la place de vos compagnons habituels... Je veux que tout soit limpide jusqu'à ce que l'affaire soit réglée !";
			link.l1 = "Comme c'est aimable de ta part. Et que se passera-t-il si notre bon ami décide de jouer sale ? Je préfère confier mon sort à des gens que j'appelle amis, et qui savent quoi faire dans de telles situations, plutôt qu'à des gens qui sont nés dans les bonnes familles.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, arrête de te comporter comme si ce duel était entre toi et moi. C'est une affaire sérieuse. De Chievous n'est pas un homme que tu peux tuer impunément. Toute issue sera suivie d'enquêtes, peut-être même d'un procès. Nous aurons besoin de témoins dignes de confiance. Tu vois, je veille sur toi ! La chose la plus importante cependant est que tu ne peux pas le tuer. Je comprends, Angerran est déterminé et probablement un combattant décent mais, Charles, tu ne peux pas le tuer ! Blesse-le, humilie-le même, mais arrête-toi là. Si tu le tues - il y aura des conséquences et aucun de nous ne pourra les esquiver ou y survivre. Même si le comte de Levi Vantadur n'a jamais officiellement reconnu son bâtard, il n'a pas d'autres fils. Sa rage n'aura pas de fin.";
			link.l1 = "Magnifique, donc je préférerais me faire tuer plutôt que de te laisser éjecter de ton poste de gouverneur par ce comte enragé ?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Je crains que si vous n'écoutez pas, nous ne survivrons pas beaucoup plus longtemps qu'Angerran de Chievous. Souvenez-vous de cela et soyez prudent. Le duel est prévu pour dix heures ce soir, après les portes de la ville. Mes officiers vous y retrouveront. Maintenant, pour le dernier point : Madame Julianne Botot - comment va-t-elle ?";
			link.l1 = "Tu veux savoir si j'ai déjà profité de mon prix ? Non, Excellence, pas encore ou jamais - peu importe. Ce qui importe, c'est que tu es banni à jamais de la demeure de la marquise. Elle a été limpide à ce sujet. Je ne peux pas la juger pour cela. Julianne choisira elle-même son prochain protecteur.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Tu sais vraiment comment surprendre, Charles. Quoi qu'il en soit, j'ai une réunion ennuyeuse avec l'agent de la Compagnie à laquelle je dois assister. Tu devrais y aller aussi, te préparer et je me souviens de ce que je t'ai averti.";
			link.l1 = "Je vais certainement essayer, Excellence. Mais c'est une bataille, donc je ne promets rien. Merci de m'avoir aidé.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Tu es vivant, Charles ! Quel soulagement, comment t'en es-tu sorti ? Est-ce du sang ?! De Chievous s'en est-il sorti ?";
			link.l1 = "Malheureusement oui. Il est blessé, mais pas gravement. Il a dû fuir, mais il avait aussi lancé ses voyous contre nous. Bref, une partie de ce sang n'est pas le mien.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Salaud ! Et mes hommes ? Sont-ils vivants pour témoigner de ce qui s'est passé ?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Ils vont bien, Excellence. Un peu amochés, mais ils vivront.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Pas tous, Excellence. Un gentilhomme n'a pas survécu - de Chievous s'est donné la peine d'amener des mousquetaires. Je n'ai rien pu faire.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "C'etait l'enfer dechainé là-bas, Excellence. Les deux braves gentilshommes sont tombés au combat. Si ce n'était pas pour eux, les choses auraient mal tourné pour moi. De Chievous a orchestré une sacrée embuscade.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Splendide ! J'obtiendrai leurs témoignages écrits en présence de témoins dignes de confiance. De Chievous payera pour cela !";
			link.l1 = "Je ne pense pas que nous puissions même causer le moindre tort à son nom. Je préfère le trouver et terminer le travail moi-même malgré tous tes avertissements. Un tel lâche ne mérite pas de vivre.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Terrible. Mais nous obtiendrons au moins un témoignage écrit d'un témoin. De Chievous paiera pour ça !";
			link.l1 = "Je ne pense pas que nous puissions causer le moindre dégât à son nom. Je préfère le trouver pour terminer le travail moi-même malgré tous vos avertissements. Un tel lâche ne mérite pas de vivre.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Maudit soit-il ! C'étaient de bons hommes, Charles ! Je jure, le salaud paiera !";
			link.l1 = "Je ne pense pas que nous puissions même entacher son nom le moins du monde. Je préfère le trouver pour finir le travail moi-même malgré tous tes avertissements. Un tel lâche ne mérite pas de vivre.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Oublie ça, Charles. Le salaud a fait tous les dégâts nécessaires lui-même. Je parierais qu'il est en fuite maintenant, caché dans la boue d'une pauvre colonie. Il est peu probable qu'il soit encore une menace pour toi. Cette vilenie n'était qu'une morsure de serpent en fuite. Tu sembles être blessé aussi, as-tu besoin d'un médecin ?";
			link.l1 = "Merci de vos préoccupations, Excellence, mais je vais bien.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Bon à savoir. Vous pouvez respirer librement maintenant, cette histoire est terminée. Détendez-vous et retournez à vos affaires. À propos, à ce sujet... Nous n'avons pas terminé notre précédente discussion sur vos récents gains. Avez-vous décidé ce que vous allez en faire... d'eux ?";
			link.l1 = "Je ne te suis pas très bien, Jacques. Quoi ça? Parles-tu de la marquise? Merde! Madame Botot! De Chievous est en fuite, il ne représente plus une menace pour moi, mais il est désespéré et il peut tout faire! Je dois y aller! Envoyez les gardes à la maison de la marquise! Maintenant!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Un capitaine célèbre, dites-vous ? Celui qui a repoussé l’assaut espagnol et a failli raser cette petite ville ? Je vois. Qu’est-ce que vous prenez ?";
			}
			else
			{
				dialog.text = "Un capitaine célèbre, dites-vous ? Je n’ai jamais entendu parler de vous... Qu’est-ce que vous prenez ?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, comme notre belle hôtesse ? Es-tu sûr de pouvoir bien goûter après tout ce sel marin ? Normalement, les gens de ton acabit préfèrent boire des choses qui peuvent dissoudre une vieille botte.";
			link.l1 = "Si c'était une suggestion de passer les portes ensemble, alors je suis partant. Je ne t'aime pas non plus et je suis heureux que le sentiment soit réciproque. Arrêtons de parler, de toute façon tu n'es pas doué pour ça. Je te laisse le choix des termes et des armes.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Un bouquet de terre et de pisse de chat ? Charmant ! Ils ne font même pas vieillir cette merde aigre en barriques, car ça ne deviendra jamais du vin, de toute façon. Dis-moi, le sel de mer martèle-t-il un goût aussi fort ?";
			link.l1 = "Si c'était une suggestion de passer ensemble les portes, alors je suis partant. Je ne t'aime pas non plus et je suis content que le sentiment soit réciproque. Arrêtons de parler, tu n'es pas doué pour ça de toute façon. Je te laisse le choix des termes et des armes.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, quel garçon courageux ! Maintenant, calme ton tempérament et garde tes distances. Nous ne sommes pas dans une taverne et je ne suis pas ton compagnon de beuverie. Tu es bien en dessous de ma classe, nous ne devrions même pas parler, mais la dame l'a demandé. Maintenant, Jacques et moi avons une affaire inachevée...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, es-tu bien ? De l'eau, imbéciles ! Apportez de l'eau !";
			link.l1 = "... ";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Tu as bien raison, il fait lourd ici. Jusqu'à présent, le jeu a été des plus divertissants, mais faisons une petite pause avant le final. Adieu, adieu Jacques - te souviens-tu des termes de notre tournoi ?\nEt voici Charles de Maure, n'est-ce pas ? Un capitaine au goût douteux pour le vin, je me souviens de toi. Ne t'inquiète pas, une fois que j'en aurai fini ici, tu ne boiras plus que de l'eau. Alors prends ton temps, profite du moment, bois quelque chose. Quand tu seras prêt, viens me rejoindre dans cette petite pièce. Nous terminerons la nuit dans un environnement plus confortable...";
			link.l1 = "Je m'en réjouis, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Te voilà, enfin. Prêt à te séparer de ton argent ?";
			link.l1 = "Je prefererais ajouter le tien aux leurs. S'il te plait!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Bien dit, hélas notre cher gouverneur a insisté pour changer les règles juste avant sa honteuse défaite. Maintenant, nous sommes obligés d'ajouter quelque chose de plus à l'argent en jeu. Les enjeux doivent être reconnus égaux par les deux parties. Mon enjeu est la flûte en argent.";
			link.l1 = "Allons-y, c'est ennuyeux - je peux en avoir cinq avec de l'or en quelques semaines de pillage. Donne-moi quelque chose de plus gros.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Oui, j'ai vu votre navire, je dois admettre qu'il est vraiment un spectacle à admirer. Élevons-le donc - deux navires contre un. Ma frégate et flûte avec de l'argent contre votre navire ?";
				link.l1 = "Un jeu digne ! Madame Botot avait tort - CE duel vivra dans les légendes. Marché conclu !";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Regardez cela, notre capitaine est un garnement ! Cependant, la course est sacrée. Que diriez-vous d'un navire de guerre alors ? Une frégate, 48 canons. Plus rapide que bien des corvettes - un produit des chantiers royaux, encore amélioré par les meilleurs charpentiers du monde. Les couleuvrines qu'elle porte ont une excellente portée et précision. Qu'en dites-vous ?";
					link.l1 = "Beaucoup mieux, je suis partant ! Allons-y !";
				}
				else
				{
					dialog.text = "J'ai entendu dire que vous avez jeté l'ancre ici, Capitaine. Soyez reconnaissant que j'aie accepté de prendre votre vieille baignoire comme enjeu. Venez donc, à moins que vous ne refusiez ?";
					link.l1 = "D'accord, tu as raison. Allons-y.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Jeu terminé, Capitaine, vous avez obtenu ce que vous vouliez. Jubilez si ça vous chante. Je propose que nous discutions des termes du rachat de ma frégate demain midi.";
					link.l1 = "C'est tout ? Je crois sincèrement, tout comme toi, que ce qui est perdu dans un pari ne peut être racheté, seulement regagné. Ou je peux la vendre en bois aux pêcheurs locaux et leur raconter tout sur ton généreux don.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Ainsi la Fortune a eu son mot à dire. Cela s'est avéré des plus curieux. Félicitations. Capitaine de Maure. Je suggère que nous discutions des termes du rachat de ma frégate demain midi.";
						link.l1 = "C'est si tôt ? Nous décevons d'autres invités, monsieur. Si je me souviens bien, il vous reste encore un navire. Je crois sincèrement, tout comme vous, que ce qui est perdu dans un pari ne peut être racheté, seulement regagné.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "Alors, la Fortune a eu son mot à dire. Cela s'est avéré des plus curieux. Félicitations, Capitaine de Maure. Vous avez mérité un bon verre, essayez le Sangiovese. Je suppose que Jacques vous paiera bien pour cette barcasse, il semble qu'il y tienne, bien plus que pour d'autres certaines choses. Cela suffira pour acheter un bon vin.";
						link.l1 = "Vous rendez-vous déjà ? Nous décevons les autres invités, monsieur. Si je me souviens bien, vous avez encore un navire. Je parie votre frégate contre ma flûte avec de l'argent puisque vous avez jugé mon propre navire trop modeste.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Malchance, Capitaine. Néanmoins, j'apprécie votre bravoure, de plus je suis de bonne humeur aujourd'hui. Je prendrai votre or mais vous pouvez garder votre navire. Disparaissez de ma vue et évitez de jouer à l'avenir, je vous prie. Un jour, cela vous tuera.";
				link.l1 = "Très noble de votre part, je ne m'y attendais pas. Adieu, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Il y a une différence notable entre fanfaronner et se moquer de votre adversaire vaincu, monsieur de Maure.";
			link.l1 = "Te considères-tu déjà vaincu? Mais tout avait si bien commencé... ah! Madame Botot, croyez que votre salon vient de s'enrichir d'une histoire mémorable sur les écarts entre paroles et actes!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Que veux-tu de plus ? Je n'ai pas d'autres navires dans ma manche ni assez d'argent pour couvrir ne serait-ce qu'un seul navire. Jouer des doublons n'est pas sérieux après tout ce que nous avons vu ce soir aussi.";
			link.l1 = "Es-tu moins ingénieux que notre cher Jacques Dille do Parkuet ? Je te fais cadeau de la plus belle occasion de prouver que tout l'amour n'est pas à vendre. La fortune ne vend pas non plus sa faveur. Le navire d'argent et ta frégate contre ce que tu estimes plus que l'or.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Capitaine, cela n'est même pas drôle. Finissons-en - l'aube approche. Nous discuterons du rachat de ma frégate demain.";
			link.l1 = "Très bien, tu l'as - trois navires ! Y compris un véritable vaisseau de guerre contre la dame la plus... eh bien, coûteuse du Nouveau Monde. Peux-tu même refuser un tel enjeu ?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Ce serait une folie. Pourtant, c'est une folie, monsieur de Maure. S'il vous plaît. Mais souvenez-vous, c'était votre idée.";
			link.l1 = "Ça va être la légende qu'ils savoureront pendant un an à huis clos ! Hé toi, plus de vin et de bougies ! Le jeu doit continuer !";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Tout récemment, tu as considéré cette flûte comme une mise indigne contre nos navires. Qu'est-ce qui a changé ?";
			link.l1 = "Je me suis ennuyé. Ajoutons un peu de piquant à notre duel - ta frégate et mon navire contre...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "La flûte que tu as si peu estimée ? Es-tu en proie à la fièvre par hasard ? Tu n'as pas l'air trop bien.";
			link.l1 = "Je vais parfaitement bien, merci. Vous n'avez pas écouté. Des enjeux de deux contre un ne sont pas vraiment spectaculaires, c'est vrai, alors égalisons les chances ! Toutes les valeurs ne peuvent pas être mesurées en or, n'est-ce pas ? Ou peut-être préférez-vous simplement ne pas lutter contre le vent, si quelque chose ne se passe pas comme prévu, vous changez de cap ? Dommage alors, il semble que je me sois trompé sur votre compte. Madame Botot, je crois que votre salon vient de recevoir une autre histoire riche sur les différences entre dire et faire...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Ne tentez pas de m'énerver, monsieur de Maure, vous êtes bien trop naïf pour cela.";
			link.l1 = "En effet. Le manque de volonté n'est pas un péché... sauf si vous êtes un homme de guerre bien sûr. Ou un noble, l'honneur familial, comme vous le savez peut-être, est parfois un tel fardeau. Il est peu probable que vous soyez familier avec de tels dilemmes cependant.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Essayez-vous de commencer un duel ou de continuer une partie ?";
			link.l1 = "Les deux feront l'affaire. Je vais rendre hommage à la collection de vins de la Marquise pendant que tu te ressaisis.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Ainsi soit-il. Cette nuit doit se terminer convenablement. Deux grands navires contre la vieille barcasse remplie d'argent et la meilleure femme de la Nouvelle-France ! Respirez plus profondément, monsieur de Maure, cet enjeu deviendra une légende parmi les commérages de la haute société.";
			link.l1 = "Votre défaite deviendra une légende, en effet, monsieur de Chievous. Apportez-nous plus de vin et de chandelles ! Allons-y !";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Vous avez perdu la tête à cause de la chance, monsieur de Maure. Vous risquez ici, la faveur du sort est éphémère.";
			link.l1 = "Une faveur brève est un chemin vers le véritable amour. Ce qui peut être dit de la loyauté achetée. Elle ne mène qu'au mépris ou à l'ennui.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Tes tentatives pour me titiller m'amusent. Tu ferais mieux de demander à madame Juliana des choses comme la faveur, l'amour et tout le reste que tu peux acheter ou non. Mais fais vite - elle quitte la ville demain.";
			link.l1 = "Au moins, votre connaissance du sujet est unilatérale. Vous ne pouvez pas gagner la faveur de Dame Fortune ni en gagnant ni en payant ici, donc vous ne pouvez pas connaître son amour. Il faut du courage, monsieur, et une volonté inébranlable pour prendre des risques. Sans parler du fait que des dames plus... terrestres apprécient aussi ces choses. Je parie deux de mes navires contre un des vôtres, êtes-vous partant ?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Tu veux continuer avec tant de hâte ? Très bien, peu importe. Mais ajoutons un peu de drame à tout cela, monsieur de Maure. Vous disiez quelque chose à propos de l'amour et des prix ? Je propose donc d'équilibrer nos enjeux - cette barcasse à toi et la flûte en argent contre ma frégate et la meilleure femme de la Nouvelle-France. Qu'en dis-tu maintenant ?";
			link.l1 = "Je dis que vous savez certainement jouer avec style, monsieur ! Plus de vin et de bougies ! Allons-y !";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Incroyable, monsieur de Maure, c'est tout simplement incroyable !";
				link.l1 = "Ouais, c'est ça, l'Europe n'avait pas connu pareille défaite depuis la bataille de Rocroi, monsieur de Chievous. Un artiste qui réside quelque part en moi tremble de désir de peindre un tel moment historique. C'est dommage que je ne dessine plus comme je le faisais dans ma jeunesse. Mais peut-être que madame Julianne doit avoir un artiste talentueux dans son entourage, ai-je raison ?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Pas de chance, Capitaine. Néanmoins, j'apprécie votre bravoure, et je suis de bonne humeur aujourd'hui. Je prendrai votre or mais vous pouvez garder votre navire. Hors de ma vue et, je vous prie, évitez de jouer à l'avenir. Un jour, cela vous tuera.";
				link.l1 = "Très noble de votre part, je ne m'y attendais pas. Adieu, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Non, tu ne comprends pas. C'est si incroyable que cela ne peut tout simplement pas être !";
			link.l1 = "Nous avons tous vu les cartes, monsieur de Chievous - la Fortune ne ment jamais.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "La fortune ne le fait pas, mais vous, monsieur de Maure, vous le faites ! Il me semble que derrière votre impudence, il y avait un plan, pas seulement de la passion. Vous êtes un menteur et un tricheur - je suis prêt à le confirmer devant tous les invités.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, ai-je bien entendu? Vous êtes prêt à confirmer vos soupçons non seulement par des mots? Il semble que vos insultes vont trop loin et moi, contrairement à vous, je tiens à l'honneur de ma famille.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Second fils, un tricheur et un escroc ne va pas me parler d'honneur familial ! Tais-toi, Julianne, je m'adresserai à toi plus tard ! Charles de Maure, j'insiste pour que tu me donnes satisfaction immédiatement ! Épée ou pistolet ?";
			link.l1 = "Les deux. Pour être honnête, je suis heureux que vous ayez changé d'avis. Rappelez-vous, je vous ai suggéré de nous promener au-delà des portes ? Que disiez-vous de ma classe indigne ? Peut-être que le jeu de cartes vous a finalement doté d'un peu de courage ?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Un honneur trop grand mais je suis d'accord avec la marquise. Je te finirai comme un noble, de Maure, même si tu ne le mérites pas. Je te défie en duel demain à midi, par l'entremise de Son Excellence le gouverneur. Viens le voir toi-même ou envoie tes seconds pour discuter des termes. À bientôt. Madame, mes respects.";
			link.l1 = "... ";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Et te voilà, le favori de la fortune. Tu t'es occupé de tes affaires, j'espère ? Tu n'as pas oublié de te confesser ? On dit que l'enfer peut être plutôt inconfortable sans cela.";
			link.l1 = "Les paroles sont bon marché, monsieur. Vous ne savez pas jouer aux cartes correctement, alors mettons vos compétences en escrime à l'épreuve... En garde!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Bien joué, maudit soit-tu. Mais je vis encore !";
			link.l1 = "Ta blessure n'a pas l'air bonne, mais tu devrais tout de même te montrer à un médecin. Clairement, tu ne peux pas continuer comme ça, tu mourras si tu le fais. On dirait que nous en avons fini ici. J'ai gagné, et je n'ai pas triché. Je te rendrai ton navire et tu quitteras St. Pierre. Nous ne nous reverrons jamais.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Quelle chevalerie énorme ! Regardez, monsieur de Maure, vous êtes peut-être un escrimeur né, mais vous avez certainement triché aux cartes. J'ai tripoté le jeu trois fois. Trois fois, bon sang ! Aucun miracle au monde ne pourrait vous sauver, mais vous avez quand même gagné ! J'aimerais savoir comment vous avez fait... Peu importe, bientôt vous le raconterez au Diable. Frappez-les, gars !";
			link.l1 = "Espèce de salaud ! Je t'ai montré de la clémence et c'est ainsi que tu me remercies ?! Messieurs, aux armes !";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "J'admets, Monsieur de Maure, je suis un peu surpris de vous voir ici. Cela signifie que je ne me trompais pas à votre sujet et que la sauvageonne signifie quelque chose pour vous ?";
			link.l1 = "Je me demande quelle est l'opinion de votre bon ami de Lyons sur l'enlèvement d'officiers appartenant à des capitaines respectés de notre Marine ? Peut-être devrions-nous lui demander de nous rejoindre et lui raconter toute l'histoire ?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Ca ne vous aidera pas du tout, croyez-moi. De plus, j'ai traité votre catin mieux qu'un général captif. Pour l'instant. Mais tout peut changer et c'est à vous de décider, Charles.";
			link.l1 = "Je ne me souviens pas que nous ayons eu une affaire amoureuse. Ne me Charles pas, Monsieur de Chievous. Va droit au but et dis-moi ce que tu veux de moi ?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "De toi ? Rien, Dieu m'en garde ! Toi et moi venons de régler une triste querelle après un jeu de cartes scandaleux, avons bu quelques verres et avons quitté cette pièce en bons vieux amis.";
			link.l1 = "Angerran, tu as l'air bien malgré ta blessure récente et chaque minute de ce bavardage inutile me donne envie de remédier à cela. Même l'idée de gâcher ces beaux tapis de François de Lyons devient de plus en plus séduisante pour moi.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Mais le bon vieux Francois adore ces tapis, Charles. Tout le monde aime quelque chose. Puisque tu es ici, tu dois aimer ta petite amie d'armes. Je suis prêt à te la rendre en échange de ma propriété. Tu as gâché le jeu et même si je ne pardonne généralement pas de telles transgressions, je peux faire une exception pour toi. Tu me donneras le prix que je désire tant et je te donnerai le même. Puis nous nous séparerons magnifiquement. Voilà pour l'amour.";
			link.l1 = "Tu penses que je porte la marquise comme un putain de bijou dans ma bourse ? Foutaises ! Comment pourrais-je te la donner ?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Je m'en fiche complètement, Charles. Tu as deux semaines pour t'en occuper. Et oui, je veux que ce prix soit reçu secrètement. Disons, un capitaine qui aurait gagné une courtisane ridiculement chère, mais qui n'a pas réussi à obtenir ses faveurs malgré tout, pourrait faire quelque chose de stupide à ce sujet, n'est-ce pas ? Tu penses que tu es déjà assez désespéré, Charles ?";
			link.l1 = "Je veux d'abord voir mon officier pour m'assurer qu'elle est encore en vie.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Il n'en est pas question. Vous devrez me faire confiance. Elle reste en lieu sûr et elle y restera jusqu'à ce que j'obtienne mon prix. Mais si vous insistez pour la voir avant, je me ferai un plaisir de vous envoyer une partie d'elle. Quelles sont vos préférences ? Une oreille, un nez, quelques doigts ?";
			link.l1 = "Pose un doigt sur elle, vermine, et je te jure que je t'étranglerai de mes propres mains, par Dieu! Ne me mets pas à l'épreuve, sacripant!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Calme-toi. Tout ce qui va se passer dépend entièrement de toi. Je n'aime pas la violence, je ne l'utilise que lorsque je dois. Ne me force pas. Remets-moi mon prix à Cape Scott Head à la Dominique dans moins de deux semaines et tu recevras ce qui t'appartient. Je me fiche de la manière dont tu le feras. Si tu veux voler - vole, tu es un pirate après tout, seulement bien habillé.";
			link.l1 = "Tu es complètement cinglé, il y a une sacrée différence entre un pirate et un foutu marchand d'esclaves...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Respire plus profondément, nous allons défiler avec élégance devant le vieux François. Nous sommes amis maintenant, tu te souviens ? Souris Charles, allez ! Séparons-nous ici. Cap Scott Head, Dominique, deux semaines. Ne sois pas en retard.";
			link.l1 = "Je te verrai là-bas.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Bonsoir, madame Botot, capitaine de Maure. Je vous demande de rester calme.";
			link.l1 = "Marquise, derrière moi, maintenant ! Monsieur, que signifie cela ?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "J'ai une douzaine d'hommes derrière la porte et des pouvoirs d'urgence autorisés par votre État. Les gardes ne vous aideront pas. Donc, s'il vous plaît, rangez votre épée, monsieur. Je veux juste discuter. Pour l'instant.";
			link.l1 = "Monsieur, qui êtes-vous et comment êtes-vous arrivé ici ?! Vous devriez vous expliquer !";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Permettez-moi de me présenter - monsieur William Cortney, Baronet Cortney. Maintenant, calmons-nous tous et discutons.";
			link.l1 = "D'accord, Monsieur Cortney, nous sommes tout ouïe.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Veuillez m'excuser d'avoir écouté aux portes, mais les circonstances actuelles ne me laissent pas d'autre choix. Bien que je reste anonyme ici à Saint-Pierre, je mène une enquête extrêmement importante au nom de la Couronne d'Angleterre. Concernant un navire de courrier perdu en mer. Avez-vous déjà entendu parler d'une brigantine la Regina ? ";
			link.l1 = "Je n'ai pas suivi et je ne comprends pas vos allusions douteuses, Monsieur. Je suis un capitaine honnête...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Je me fiche éperdument de vos petites affaires louches, monsieur. J'ai mené quelques recherches à votre sujet et, pour être honnête, vous avez été mon premier suspect quand j'ai entendu dire que vous aviez visité la Martinique juste après la disparition de la Regina. Cependant, vous n'êtes pas un idiot et vos hommes n'ont pas joué avec des perles ici. Par conséquent, vous êtes hors de mes soupçons, pour l'instant.";
			link.l1 = "Des perles ? De quelles perles parles-tu, vieux fou ?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Perles de grande taille, soigneusement choisies, provenant des opérations de la Côte Ouest espagnole. Les perles sont noires aussi, ce qui signifie qu'elles sont extrêmement rares, en as-tu déjà entendu parler ?";
			link.l1 = "Je suppose, pourtant j'ai toujours pensé que c'était juste une autre histoire de marin à la noix. Pareil que les histoires sur le Vaisseau Fantôme. Julianne, qu'est-ce qui ne va pas ?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Je dois vous demander de le présenter ici, madame. C'est une affaire de la plus haute importance. Pendant ce temps, vous, monsieur, devez tout me raconter sur le capitaine Moreno. Je soupçonne que c'est lui qui vous a donné cette piste. Je suis très curieux d'apprendre quel rôle il joue dans cette affaire.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno n'est pas son vrai nom, Monsieur Cortney. Son nom est Hernando Vasquez, aussi connu comme le Don Sanglant, un pirate espagnol qui était quartier-maître de l'Albatross - le navire de l'infâme Bartholomew le Portugais.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Nous n'avons échangé que quelques mots. Je n'ai pas grand-chose à raconter. Il avait l'air d'un vrai loup de mer.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Eh bien, eh bien. Et puis-je demander comment le savez-vous?";
			link.l1 = "Je connaissais son capitaine. En fait, c'est moi qui l'ai capturé et livré aux Hollandais. C'est une longue histoire. C'est dommage que je n'aie pas eu Vasquez lui-même à l'époque...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Vous êtes vous-même un loup de mer, monsieur. Je ne crois pas que vous ayez manqué de remarquer plus.";
			link.l1 = "Juste un léger accent, la façon dont il regardait et se comportait. Je parie qu'il est Espagnol, Monsieur Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "C'est un casse-tête, monsieur. Et c'est mauvais. Madame, avez-vous trouvé le collier? Laissez-moi l'inspecter\nOui, en effet, c'est l'une des perles noires espagnoles. Regardez, ces foutaises de marin sont bel et bien réelles. Tout ce qui reste, c'est de découvrir comment ce de Chievous a obtenu l'une d'elles. Au fait, n'est-il pas un bâtard du Duc de Levy Vantadur?";
			link.l1 = "C'est bien lui. À notre connaissance, il avait des affaires avec le baron pirate local à Le Francois. Peut-être a-t-il acheté cette perle de lui ?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Peut-être bien. Mais je n'aime pas du tout la piste espagnole dans cette affaire. Quoi qu'il en soit, merci pour votre coopération. Je crains de devoir vous rendre visite à nouveau demain à la même heure. Je demanderais également la présence du capitaine de Maure. Peut-être aurai-je plus de questions pour vous. Je devrais aller à Le François maintenant.";
			link.l1 = "Monsieur Cortney, attendez. Peut-être pourrais-je vous rejoindre ? Jacques Barbazon n’a pas gagné son surnom pour être une personne aimante et douce, de plus, cette affaire m’intéresse aussi.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Capitaine, je suis touché par votre sollicitude mais c'est non. C'est une affaire d'État. Le vaurien connaît sa place et n'oserait pas toucher l'émissaire de la Couronne, sinon son village misérable n'existerait plus ! Je m'excuse encore pour l'intrusion, madame. Bonne soirée.";
			link.l1 = "À demain soir, Baronnet.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Ne lui en voulez pas, Capitaine. Je peux être très persuasif. Votre histoire est impressionnante, vraiment. Je crois que je pourrais avoir besoin de vous.";
			link.l1 = "Tu as l'air content, comment ça s'est passé à Le Francois ?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Comme je m'y attendais, ton baron était doux comme un agneau. Il m'a dit tout ce que je voulais entendre. Comme je l'ai dit, je peux être extrêmement persuasif.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Aujourd'hui, je suis venu ici seul, il n'y a aucun de mes hommes derrière cette porte. Que diable ?!";
			link.l1 = "J'ai un mauvais pressentiment à ce sujet. Julianne, mets-toi derrière moi, maintenant ! Baronet, les émissaires de la Couronne se battent-ils aussi bien qu'ils parlent ?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Tu sais manier l'épée, Capitaine ! Euh, pour être honnête, ce n'était pas de tout repos. Qui diable étaient ces gens ?!";
			link.l1 = "Nous devrions demander à leurs amis - j'entends plus de pas. J'aimerais que ce soit les gardes...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Incroyable ! Tu penses que le salaud a osé faire tout ça ?! Il paiera, je le jure !";
			link.l1 = "Respire. Barbazon trouvera comment se tirer d'affaire face à n'importe quelle accusation. Il te dira que ce n'était qu'un simple raid de petits voleurs sur une maison riche. De plus, c'est un foutu pirate, pourquoi se soucierait-il des autorités ! Quoi qu'il en soit, maintenant je suis sûr que tu as réussi à apprendre quelque chose de vraiment valable. Je te demande de partager ce savoir avec moi.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Je ne peux pas vraiment dire non, n'est-ce pas ? Sinon, la prochaine tentative pourrait bien réussir ? Très bien, je ferai semblant de ne pas avoir remarqué la menace dans ton ton. Disons que je te rends un service. Jacques Le Gentil n'a pas vendu des perles à ton bâtard noble. Il en achetait. Voilà.";
			link.l1 = "Donc c'était de Chievous qui a intercepté la Regina ? C'est un vaurien, mais il est difficile de croire qu'il se rabaisserait à une piraterie ordinaire.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "On n'appellerait guère la Regina un prix ordinaire pour un pirate, Capitaine. Nous supposons qu'elle avait au moins une demi-douzaine de perles noires. Même une seule perle noire est inestimable. Je dois absolument rencontrer ce monsieur de Chievous à tout prix.";
			link.l1 = "Je peux vous être d'une certaine aide ici, Monsieur. Mais laissez-moi clarifier quelque chose d'abord. Il ne me semblait pas que je me souciais du collier de madame Botot, donc les perles ne sont pas la raison de votre présence ici. Qu'avait d'autre la Regina à bord ?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Très bien, je suppose que je vais devoir vous en dire plus compte tenu des... circonstances. Voyez-vous, la cargaison n'est pas aussi importante comparée au navire lui-même. La brigantine de courrier, la Regina, avait été assignée à un port de San Jose, Trinidad. Son capitaine avait l'habitude de rassembler des informations et de faire quelques... courses pour nous.\nSa dernière course consistait à transporter les butins que nos filous avaient réussi à extraire des opérations de perles espagnoles. Il nous a fallu trois ans d'efforts pour obtenir cette piste. Les perles noires sont certes significatives, mais perdre la Regina est funeste. Ce n'était pas un accident, quelqu'un qui savait pour ses perles devait aussi avoir connaissance du reste.";
			link.l1 = "Splendide, alors c'est une affaire de services de renseignement après tout ! Craignez-vous que tout le réseau d'espionnage que vous avez construit soit en danger ? Maintenant, je peux voir toute l'étendue de vos ennuis.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Vous avez déjà entendu parler de John Thurloe ? Il est le chef du renseignement de la Couronne. Un jour, je serai à Londres pour lui faire un rapport personnellement sur le sort du Regina. Je dois trouver où est la fuite et... m'occuper de la source. De plus, il y a aussi ce mystérieux capitaine Moreno qui vous appartient. Si les Espagnols ont suivi notre réseau d'espionnage colonial, des années de travail ardu et laborieux partiront en fumée !";
			link.l1 = "Tu sais, tout cela commence à avoir du sens si tu regardes le tableau d'ensemble. Je commence à penser que quelqu'un avec un accent espagnol a parlé à de Chievous de la Regina et des perles noires.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "Nous pensons de la même manière. Il n'y a pas de meilleure façon d'exploiter un réseau d'espionnage découvert. Un incident diplomatique impliquant un homme d'un rang si élevé... Un tel incident peut sérieusement nuire aux relations entre la Grande-Bretagne et la France, il suffit de fournir les bonnes pistes et d'attendre un scandale international. Peut-être même que cette piste sur les perles noires nous a été délibérément donnée aussi.";
			link.l1 = "Ces maudits Castillans, n'est-ce pas ? Alors, que faisons-nous à propos de de Chievous ?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Pour être honnête, je n'en ai aucune idée. Si c'est une provocation espagnole, il serait sage de simplement l'ignorer. Mais je dois apprendre comment il a découvert le Regina et à quel point cela nuit à notre réseau dans les colonies espagnoles. Je te dois aussi la vie, et j'ai l'intention de te rembourser.";
			link.l1 = "Honnêteté pour honnêteté, Baronnet. Je pourrais utiliser toute l'aide que je peux obtenir. Je suis déjà assez désespéré pour envisager d'enlever la marquise.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Tu te rends compte que c'est ainsi que de Chievous brouille les pistes ? Il sera si facile de mettre tout ce bazar sur toi, y compris la disparition de la Regina. Par conséquent, je propose la chose suivante. La marquise Botot m'a dit que de Chievous ne participera pas à l'échange et restera prudemment à Basse-Terre. Soit il a compris dans quel pétrin il s'est mis, soit il commence à soupçonner quelque chose. Il sera aussi prudent qu'une souris de cuisine. C'est pourquoi je vais aller à la Dominique avec toi.";
			link.l1 = "Mais sa prisonnière est ma priorité, je ne peux pas risquer sa vie! Elle est une otage en attente d'un échange!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "N'aie crainte - je vais presser Jacques Dille de Parkuet et obtiendrai un mandat d'arrêt pour le navire de de Chievous. Je doute que ses hommes soient pleinement conscients de la situation dans laquelle ils se trouvent, sinon ils auraient été plus prudents avec ces perles. Nous irons les voir sur une chaloupe et leur présenterons un mandat directement.";
			link.l1 = "Oui, je me souviens de votre don de coercition, Monseniour, mais c'est un risque. Et un lourd.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Tu as tout à fait raison, mais tu devras l'accepter si tu souhaites recevoir mon aide. Une fois que nous aurons terminé à la Dominique, j'irai à Basse-Terre et exigerai que le gouverneur de Lyon livre ton adversaire. Mes pouvoirs le permettent. Nous ne pouvons pas laisser de Chievous s'échapper.";
			link.l1 = "Es-tu vraiment prêt pour cela, Monsieur? Cela pourrait déclencher une guerre, n'est-ce pas?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Je parie qu'ils ne laisseront jamais cela arriver. C'est définitivement hors de question puisque nous connaissons déjà la vérité. La politique est une catin, Capitaine. Je promets d'introduire de Chievous dans les donjons britanniques, juste pour vous personnellement. Cela semble être une solution que même son père considérerait comme un prix raisonnable.";
			link.l1 = "Je ne puis dire que j'aime ton plan, mais je ne vois pas d'autre solution.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Je vous assure que nous y arriverons. Je devrais aller voir un gouverneur et donner des ordres à mes hommes. Si vous voyez la marquise, dites-lui qu'elle peut garder la perle en guise de gratitude pour son aide à l'enquête.";
			link.l1 = "Merci, Baronnet. Rendez-vous sur mon navire, nous mettrons les voiles bientôt.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Baronet Cortney, à votre service. Par le pouvoir qui m'est conféré par l'Empire britannique avec tout le soutien de son allié de confiance, la France, votre navire est par la présente arrêté. Voici les papiers, veuillez vous assurer de les lire et dites à vos hommes de garder leurs mains loin des armes. Vous êtes détenu mais pas encore arrêté. Si vous ne faites rien de stupide, vous serez libéré au premier port.";
			link.l1 = "Baronet, je dois récupérer mon... mon officier !";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Ne vous inquiétez pas Capitaine, je l'emmènerai à votre navire. Je vous demande de retourner à la chaloupe maintenant. Je prendrai le commandement de ce navire et mettrai le cap sur Basse-Terre. N'hésitez pas à nous laisser si vous n'avez pas l'intention de railler votre ennemi juré personnellement. Je vous demande seulement de me transférer quelques-uns de vos hommes pour nous aider à atteindre la Guadeloupe.";
			link.l1 = "Très bien, Monsieur. Je préfère pas. Envoyez-lui mes pires salutations. Adieu et merci encore !";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, je suis heureux de te voir. J'avais espéré ton retour mais je n'y ai jamais vraiment cru.";
			link.l1 = "De même, Baronnet. Êtes-vous venu rendre visite à la Marquise ? Où est-elle d'ailleurs ?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Tu ne comprends toujours pas, n'est-ce pas ? Elle a fui. De plus, Angerran de Chievous te présente ses sincères excuses. J'avais réussi à le convaincre que tu n'avais jamais fait partie du jeu, mais que tu en étais une autre victime. Tout comme lui. Le brave homme n'a pas pris la peine d'écrire, mais il est profondément désolé de la tournure des événements.";
			link.l1 = "Désolé à fond, n'est-ce pas ?! De quoi parlez-vous, Monsieur ?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Toi et moi, nous avons négligé l'essentiel. Comment a-t-il appris pour les perles ? Qui a invité ce capitaine espagnol dans cette même maison ? Qui a pu pousser ce salaud à poursuivre un tel trésor ?";
			link.l1 = "Tu es sérieux? Ca ne peut pas être...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Ça peut certainement. La marquise a joué son rôle à la perfection, elle a presque réussi à tout faire passer. Cependant, grâce à notre enquête, je me suis approché de Chievous non pas comme un voleur et un pirate, mais comme une victime de tromperie qu'il est. Il a découvert assez rapidement dans quoi elle l'avait entraîné, mais il n'avait pas de preuves et a décidé d'agir de son propre chef. Vous savez ce qui s'est passé ensuite.";
			link.l1 = "Tu veux dire que tout cela avait été orchestré par la Marquise ? De Chievous l'a gobé comme un enfant imprudent !";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Précisément. La passion est une chose très dangereuse, Charles ! Souviens-toi de cette nuit où tu as joué dans cette maison même ? Angerran allait extraire les preuves dont il avait besoin de la marquise en obtenant un patronage sur elle. Oui, il a triché, mais il était désespéré après des années de passion sans espoir, terminées par la plus dévastatrice des trahisons ! Mais tu es intervenu, tu t'es proclamé son champion et tu as réussi dans ce rôle. De Chievous pensait que toi et elle étiez du même avis. Il a volé un navire qu'il avait perdu contre toi pour t'empêcher d'obtenir ses journaux de bord. Il a utilisé ton officier pour essayer de vous monter l'un contre l'autre - ses ennemis mortels, comme il le croyait.";
			link.l1 = "Je suis à court de mots !";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Maintenant, tu sais comment c'est, Charles ! La Marquise est intelligente, d'une beauté à couper le souffle et non moins dangereuse. Je ne sais pas combien de temps elle a manipulé les meilleures personnes de la Nouvelle-France. De nombreuses années, dirais-je. Quoi qu'il en soit, cela ne te concerne plus. Ce fut un plaisir de te revoir, mais j'ai encore des chambres à mettre sens dessus dessous, c'est une grande maison. Nous ne trouverons probablement rien, mais il faut au moins essayer.\nUne chose de plus avant que nous ne nous séparions. Tiens, prends ça. Un souvenir pour te rappeler. Peut-être que tu l'offriras à ta dame quand tu seras prêt. Tu es très chanceux, tu sais. Surtout comparé à de Chievous, ce pauvre bougre !";
			link.l1 = "Vous avez raison, je le suis. Adieu et bon vent dans vos recherches, baronet !";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Quelle belle journée nous avons aujourd'hui, hein Capitaine ? J'ai entendu parler de vos exploits, mais je ne vous aurais jamais imaginé être un pirate banal. Quelle insolence - venir à St. Jones après ce que vous avez fait !";
			link.l1 = "Je suis peut-être un pirate, c'est bien vrai, monsieur, mais ai-je l'air d'un idiot ? Pourquoi diable viendrais-je ici après avoir pillé le Mercury et l'avoir délesté de ses perles espagnoles ?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Je l'admets, c'est la seule raison pour laquelle vous avez cette conversation maintenant au lieu de vous balancer à une corde. Voyez-vous, il y a un petit détail que nous avons caché dans cette affaire. Et je ne parle pas de la perle que nous avons trouvée sur vous. C'est le nom de la brigantine.";
			link.l1 = "Que veux-tu dire ?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Une brigantine de currier, la Regina avait été affectée au port de San Jose pendant les deux dernières années. Son capitaine nous a fourni des renseignements et a aussi exécuté... des corvées de toutes sortes. Nous la recherchons officiellement sous le prétexte du courrier diplomatique perdu qu'elle transportait. Ce n'est pas vraiment un stratagème, je l'admets. Pourtant, vous ne pourriez pas connaître le véritable nom du navire sans fouiller correctement dans la cabine de son capitaine.";
			link.l1 = "J'étais aveugle mais maintenant je vois. Je vous en prie, écoutez-moi, monsieur, je vais expliquer !";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Eh bien, fais un effort, capitaine. Ta vie ne tient qu'à un fil.";
			link.l1 = "Je n'ai rien à voir avec cette histoire d'espionnage ! Les Espagnols non plus. Votre réseau est sûr, ne vous inquiétez pas. Cependant, il y a eu une fuite et quelqu'un en a profité. Et puis, je me suis disputé avec cette personne. J'ai trouvé des preuves de son implication dans l'affaire Mercury et je voulais les utiliser pour le battre.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Que Dieu en soit témoin, je pensais que cela n'était qu'une affaire ordinaire de piraterie, je n'aurais jamais imaginé que les services secrets de la Couronne étaient impliqués ! Tout ce que j'ai, c'est cette perle, mais je sais très bien quand et où tu peux en trouver davantage.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Vous avez déjà entendu parler de John Thurloe ? Il est le chef des services secrets de la Couronne. Un jour, je serai à Londres, lui rendant compte, personnellement, du sort du Mercury. Par conséquent, donnez-moi le nom de cet adversaire misérable qui est le vôtre.";
			link.l1 = "Angerran de Chievous, bâtard du comte de Lévy Vantadur. Je suppose qu'il considérait le Mercury comme un simple transporteur de butin de flibustiers. Il aurait pu être au courant des perles, mais n'avait aucune idée de la connexion avec l'intelligence britannique.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Vous ne décevez pas, Capitaine, je vous l'accorde ! Quel choix de divertissement et d'ennemis ! Très bien. Quelles autres preuves avez-vous à part la perle ?";
			link.l1 = "De Chievous a une frégate. Je l'ai possédée... pour une seule nuit, pourtant j'ai réussi à apprendre quelque chose. C'est un homme extrêmement pédant, tu apprendras tout sur son attaque sur le Mercury à partir de son journal de bord. Je suis presque sûr qu'il possède encore une partie du butin aussi. Peut-être même plus de perles noires s'il y en avait plus d'une.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Plus d'une, tu peux en être sûr. Nous ne mettrions jamais en danger la Regina pour une cargaison de perles ordinaires. J'espère que tu comprends que je dois absolument parler avec le Monseniour de Chievous. Je me fiche des perles, mais je dois en savoir plus sur la fuite. Mes supérieurs me mettront six pieds sous terre si je ne leur livre pas un tableau complet.";
			link.l1 = "Je serais heureux d'organiser une rencontre pour vous, mais nous devons nous dépêcher ! À cet instant même, la frégate de de Chievous est en route pour la Guadeloupe, où son propriétaire réside actuellement sous la protection du gouverneur local. Je suis sûr qu'il est conscient de ce qu'il a fait et qu'il fuira le Nouveau Monde dès que possible.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Ce sont des accusations très graves de personnes très sérieuses, Capitaine. Comprenez-vous quel genre de... tempête de merde pourrait s'en suivre ? Une attaque de brigands contre un navire arborant le pavillon d'un allié ? Cela peut sérieusement compliquer les relations entre deux grandes nations. J'ai du mal à imaginer à quel point il a pu vous irriter pour vous rendre si désireux de prendre un tel risque.";
			link.l1 = "Il m'a pris quelque chose, milord. Quelque chose que je chéris plus que ma propre vie. Je dois réparer cela. Si cela mène à la guerre, alors je servirai mon pays sous son drapeau. Néanmoins, de Chievous recevra ce qu'il mérite et il est le seul à blâmer !";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Quelqu'un vous a-t-il déjà dit que vous êtes un homme de grand danger, Capitaine ? Prêt à déclencher une guerre sur la moitié du globe pour atteindre votre objectif ? Très bien, faisons-le à votre manière. Je vais aller à Basse-Terre avec vous. Je ne peux pas laisser échapper une telle piste. J'enverrai un scribe pour consigner vos preuves pendant que je prépare mon navire.";
			link.l1 = "Merci, monsieur. Mais nous n'avons pas de temps à perdre ici, je vous avertis !";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Capitaine de Maure, nous y arriverons à temps, je n'ai aucun doute en vous. Cependant, si cette aventure ne marche pas... vous me comprenez ? Je ne peux même pas vous promettre une tombe décente.";
			link.l1 = "Oui, milord. Je vous comprends parfaitement.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "Les dés sont jetés, Capitaine. J'ai exigé une rencontre avec Angerran de Chievous. Sa frégate sera fouillée dès son arrivée. François de Lyon a des doutes, mais les sceaux sur mes papiers le retiennent pour l'instant. Je vous demande de rester en ville jusqu'à ce que la situation soit résolue.";
			link.l1 = "Bien sûr, monseigneur, je comprends.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Alors j'espère que vous comprendrez cela également. Remettez votre épée à ces messieurs là-bas et suivez-les afin que je sois sûr que vous tiendrez votre promesse.";
			link.l1 = "Inoui... milord Cortney, es-tu serieux?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Mortellement sérieux. Vous restez toujours l'un de mes principaux suspects et vous laisser partir dans ces circonstances serait très stupide de ma part. Je m'excuserai auprès de vous de la manière que je jugerai appropriée, si et quand vos paroles s'avèrent vraies.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Salutation, monsieur de Maure. Allons-y ?";
			link.l1 = "Avec plaisir, quelles sont les règles ? Pour être honnête, j'étais trop occupé avec la nourriture et j'ai probablement mal entendu les conditions.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Les règles sont simples. 10 000 pesos pour une carte, nous jouons jusqu'à ce que l'un de nous se rende. Les reçus et crédits ne sont pas acceptés.";
			link.l1 = "Cela me va. Allons-y, Colonel.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Merde ! Plus jamais ! Très bien, monsieur de Maure, bonne chance pour le prochain tour.";
				link.l1 = "Mon plaisir, Colonel. Adieu.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Vous avez bien combattu, mais Dame Fortune avait son propre plan. Adieu, monsieur de Maure. Merci pour la partie.";
					link.l1 = "Oui, je suppose que je me suis surestime dans cela. Adieu, Colonel.";
				}
				else
				{
					dialog.text = "Vous avez décidé de refuser de continuer le jeu et ainsi vous avez admis la défaite ! Vous avez combattu glorieusement, mais la fortune en a jugé autrement. Adieu, monsieur de Maure, merci pour la partie.";
					link.l1 = "Ouais, je suppose que je me suis surestimé sur ce coup-là. Adieu, Colonel.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Capitaine Charles de Maure, quelle putain de surprise !";
					link.l1 = "Capitaine. Moreno mon cul! Qu'est-ce qui vous amène ici?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Capitaine Charles de Maure, mon plaisir.";
						link.l1 = "Nous sommes-nous déjà rencontrés, monsieur... Moreno ?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Capitaine Charles de Maure, mon plaisir.";
						link.l1 = "Nous sommes-nous déjà rencontrés, monsieur... Moreno ?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Capitaine Charles de Maure, enchanté.";
				link.l1 = "Nous sommes-nous déjà rencontrés, monsieur... Moreno ?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "C'est une longue histoire. Comme toujours, capitaine. Je vois dans vos yeux que vous avez des questions. Faites juste semblant de vous moquer d'un simple marin et gardez le silence.";
			link.l1 = "Ouais, ce costume chic te va bien, mon simple ami. Je dirais que tu sais comment le porter.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Seulement en de rares occasions, par chance. Aujourd'hui est ce jour. Jouons, Capitaine. Les gens regardent, ce n'est pas poli de les faire attendre.";
			link.l1 = "Bien, nous parlerons plus tard. Marché conclu... capitaine Moreno, si vous le permettez.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Je te connais un peu, mais cela n'a pas d'importance. Distribue les cartes, Capitaine de Maure, les gens veulent un spectacle.";
			link.l1 = "Curieux. Surtout ton accent espagnol avec les éloges de madame Botot pour toi. Très bien. Mer contre mer, faisons-le !";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Je me souviens bien de toi. Quand toi et mon ex-capitaine avez embroché mes gars à Le François. Ce salaud a eu ce qu'il méritait de toute façon, pas sans ton aide si je me souviens bien. Mais n'attends pas ma gratitude, tu as tué Franz Garke et je ne te pardonnerai pas pour ça.";
			link.l1 = "Le quartier-maître des Portugais ? Le Don Sanglant, n'est-ce pas ? Cette nuit devient de mieux en mieux. Allons-y !";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Vous avez décidé de refuser de continuer à jouer et par là-même vous avez admis votre défaite ! Je suppose que Dame Fortune a eu son mot à dire. Adieu, Capitaine.";
				link.l1 = "De même, monsieur Moreno. Merci pour la partie.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Je suppose que Dame Fortune a eu son mot à dire. Adieu, Capitaine, peut-être nous reverrons-nous.";
					link.l1 = "De même, monsieur Moreno. Merci pour la partie.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Je suppose que Dame Fortune a eu son mot à dire. Adieu, Capitaine, peut-être nous reverrons-nous dans d'autres circonstances, hé-hé.";
						link.l1 = "J'ai hâte de te voir, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "C'est tout. La fortune en a décidé, Capitaine. Adieu.";
						link.l1 = "Adieu, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "C'est ça. La fortune en a décidé, Capitaine. Adieu.";
				link.l1 = "Adieu, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Tellement agréable de vous voir, Monsieur le capitaine de Maure ! Pour être honnête, je m'attendais à tout voir, y compris une garde complète, mais pas vous.";
			link.l1 = "Monsieur Moreno, avez-vous quelques ennuis avec les autorités locales? Cela fait plaisir de vous voir aussi, ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Je dis, on ne peut refuser l'invitation de notre hôtesse. Du moins, pas ce genre d'invitation. Allons Charles, cesse cette comédie. La Marquise a bien fait en sorte que je sache qu'elle connaît ma véritable identité.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Madame, vous êtes charmante ! Ce nouvel ami à vous a déjà tenté de me livrer. En fait, cela ne s'est pas bien passé, et il m'a sauvé la peau tellement de fois que j'en ai perdu le compte. Quoi qu'il en soit, je lui dois une fière chandelle maintenant, donc pas besoin de menaces, ne vous inquiétez pas.";
			link.l1 = "Je t'en suis reconnaissant, Bartholomew. Angerran de Chievous m'a acculé dans une position extrêmement inconfortable et je dois absolument le faire tomber. La vie de... quelqu'un qui m'est très cher en dépend. Fais-moi confiance, cette fois rien ne m'arrêtera.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Ça suffit, Capitaine, nous sommes amis, n'est-ce pas ? Vous vous souvenez de cette course à travers la moitié de l'Archipel ? Une telle chose signifie beaucoup pour moi. Je ferai de mon mieux pour vous aider. Avez-vous déjà entendu parler du Mercury ?";
			link.l1 = "Qu'est-ce donc? Un navire?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Une brigantine britannique, pour être précis. Son rôle était de transporter le butin des corsaires du colonel D'Oyley qui avaient pillé les opérations de perles espagnoles sur la Terre Ferme. Celles qui pêchent parfois des perles noires légendaires, tu en as déjà entendu parler ? Si ma source d'information est fiable, plusieurs de ces perles avaient été stockées sur le Mercury. Il y a un mois, j'ai tendu une embuscade entre la Martinique et la Guadeloupe en attendant ces braves messieurs. Mais ce fut en vain ! Nous avons passé une semaine en mer jusqu'à devoir admettre l'échec.";
			link.l1 = "Bien, donc votre source n'était pas fiable après tout et vous n'avez obtenu aucun prix pour vous-même. Qu'est-ce que de Chievous a à voir avec tout cela ?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "J'avais les mêmes pensées jusqu'à ce que je découvre que le Mercury ne s'était jamais montré à Antigua. Imagine ma surprise quand ils l'ont vue près de Curaçao et qu'elle ne pouvait en aucun cas passer près de moi à la Martinique. Les anglais sont en furie ! Imagine manquer un tel prix et tout ! Quoi qu'il en soit, j'ai été curieux et j'ai commencé à enquêter, sur cet individu spécial qui a gâché le plaisir pour tout le monde. Un tel butin ne peut pas être vendu rapidement, alors je suis allé à Le François pour trouver le salaud et récupérer ce qu'il me devait.";
			link.l1 = "Ton histoire me dit quelque chose. As-tu déjà entendu le mot 'Karma'? Tu sais certainement comment attirer les ennuis. Mais je ne vois toujours pas en quoi cela pourrait m'être utile?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "N'allez pas trop vite, Capitaine, je suis sur le point de vous raconter la meilleure partie de mon histoire. Cet ami mal lavé mais bien habillé à vous - ses gars ont laissé une trace notable de magnifiques perles dans les magasins locaux. Une fierté des opérations perlières espagnoles qu'ils ont dilapidée en grand nombre.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "As-tu entendu, capitaine ?";
			link.l1 = "Penses-tu que de Chievous a acheté des perles volées à Jacques le Gentil et ses gars ? J'ai bien peur que cela... ne suffise pas.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "En effet, cap. Il n'achetait pas, il vendait ! J'ai parlé avec Barbazon à ce sujet et il a confirmé qu'il avait acheté une quantité importante de perles parfaites à un de ses partenaires. Il les a ensuite envoyées en Europe. Nous avons aussi cette perle noire dans le collier et le fait que le navire de de Chievous ait subi des réparations. Les ouvriers m'ont dit que sa frégate avait des trous causés par des boulets de douze livres. Qui, sain d'esprit, attaquerait jamais une frégate avec de tels joujoux ?";
			link.l1 = "Ça ressemble à notre brigantin ! De plus, je me souviens que de Chievous se vantait de la rapidité de sa frégate. Mais pourquoi cette folie ? Nous sommes en paix avec la Grande-Bretagne, pourquoi prendre autant de risques et pour quoi ? Les perles noires sont extrêmement rares, certes, mais pas introuvables.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "Et c'est là qu'il s'est trompé ! Les britons avaient déjà lancé une enquête officielle sur la disparition du Mercury, bien qu'ils l'appellent un navire courrier manquant avec des documents importants à bord. Toute piste sera généreusement récompensée, tout responsable sera sévèrement puni. Le meilleur, c'est qu'ils ont envoyé un noble officiel spécial à Antigua qui creuse maintenant sans relâche l'affaire. Je ne me souviens pas de son nom, aussi prétentieux que sa tête, mais je suis content qu'il ne soit pas à ma poursuite !";
			link.l1 = "Eh bien, ça alors ! Il semble qu'ils veulent vraiment ces perles noires. Je me demande combien ils en avaient sur le Mercury et comment tout ce savoir peut m'être utile ?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Pourquoi, la racaille a réussi à vous énerver aussi, marquise ? Sale bâtard ! Je suis aussi avec vous sur ce coup, Capitaine de Maure ! Personne n'ose voler le butin de Bartolomeo le Portugais !";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "J'ai besoin d'un vrai verre après tout ce bavardage. Marquise, puisque nous sommes amis maintenant...";
			link.l1 = "Je ne pense pas qu'ils aient du rhum dans cette maison, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Ouais, bien sûr, attire l'attention de cet enquêteur britannique sur sa frégate ! Si c'est notre plan, alors je ne reconnais plus notre bon vieux capitaine de Maure !";
			link.l1 = "Vous allez rire, mais c'est le plan. J'aurai besoin de l'aide de vous deux. Madame - vous serez la prisonnière du pirate que j'ai engagé - Bartholomew, c'est votre rôle.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "Et à propos de cette vilenie de ma part aussi ! Bartolomeo le Portugais n'a jamais enlevé une femme !";
			link.l1 = "Et il ne le fera pas, mais cela y ressemblera pour les hommes de Chievous. De plus, il n'est pas nécessaire de leur dire ton nom. Emmène notre dame à bord et rencontre la frégate d'Angerran près de la pointe du Cap Scott. Échange Julianna contre mon officier et retourne à la Martinique. Ensuite, attends le marquis et moi.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "C'était tout très fascinant et tout, tu es un vrai chevalier, Charles. Mais comment diable sommes-nous censés la ramener après l'échange ?";
			link.l1 = "Je m'en occuperai. Nous n'avons pas beaucoup de temps, alors séparons-nous. Vous et la marquise allez en Dominique pendant que je me précipiterai à Saint-Jones. Je trouverai le colonel D'Oyley ou cet enquêteur britannique et lui dirai qui est responsable de la disparition du Mercury.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Avez-vous réfléchi à la tempête de merde qui suivra sûrement après un tel incident, Capitaine ? En ce moment, Antigua est un nid de frelons et vous me dites d'y jeter une pierre. Je me souviens de guerres qui ont commencé pour moins que ça !";
			link.l1 = "Un problème à la fois... Je la ramènerai à tout prix ! Laissez de Levy Vantadur se débrouiller seul s'il est aussi puissant qu'on le dit ! De plus, de Chievous aura du mal à expliquer comment Madame Botot s'est retrouvée à bord de son navire.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Prête? Par tous les diables! Marquise, es-tu prête à être enlevée?";
			}
			else
			{
				dialog.text = "Prête? En priant! Marquise, combien de temps te faudra-t-il pour faire tes bagages?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. Mon nom est "+GetFullName(npchar)+", et voici "+GetFullName(characterFromId("GG_SecundantGG_2"))+". Son Excellence nous a demandé d'assister à votre duel avec monsieur de Chievous.";
			link.l1 = "Bonsoir, messieurs. J'espère que tout se passera bien et que personne ne mourra ce soir. Mais soyez prêts à tout de même. Ce 'gentleman' peut être une déception.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Votre inquiétude est sans fondement. Selon les termes prédéterminés de ce duel, en aucun cas les témoins ne peuvent intervenir. Mais merci de nous avoir prévenus de toute façon. Votre adversaire est arrivé. Bon vent, Capitaine. Son Excellence m'a demandé de vous dire qu'il priera pour votre... prudence.";
			link.l1 = "Je suis sûr que cela m'aidera beaucoup. Quoi qu'il en soit, commençons.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Capitaine, nous avons un problème. Notre navire est... eh bien, il n'est plus.";
			link.l1 = "Attends, quoi ?! Comment, qui ? Une unité de garde complète était censée être postée sur elle, alors de quoi diable parles-tu ?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Non, Cap, pas le navire. Elle brille. La frégate que tu as gagnée hier, donc elle est à nous aussi, hein ? Nous n'y avons envoyé qu'un équipage de prise d'une douzaine. Elle a dit que cela suffirait.";
			link.l1 = "Putain, arrête et dis-moi exactement ce qui s'est passé depuis le début !";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Aucune idee, Cap. La fregate a leve l'ancre dans les brumes du matin. La vigie a remarque son absence quelques heures plus tard quand la brume s'etait dissipee.";
			link.l1 = "Ce n'est pas possible ! Elle ne me ferait jamais ça ! Quoique... merde, on s'est disputés récemment. Pourrait-elle...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "On craint que ce soit encore pire, Cap. Des pêcheurs ont trouvé deux de nos gars de l'équipage de prise tôt ce matin. Tous deux morts, la gorge tranchée.";
			link.l1 = "Putain de cauchemar ! De Chievous ! Il a volé son navire pendant que j'étais occupé avec la marquise ! J'espère qu'elle vit... Si elle perd ne serait-ce qu'un cheveu, je...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Voudras-tu donner les ordres aux gars pour se préparer, Cap ? Nous pouvons lever l'ancre dans deux heures, tout le monde est sur les nerfs depuis ce matin, ton second en particulier, nous avons à peine réussi à l'empêcher de partir à leur poursuite.";
			link.l1 = "Il est trop tôt pour cela. Je dois... réfléchir à cela, correctement, et parler à quelqu'un. Oui! Préparez le navire! Je veux que tout le monde soit prêt, nous lèverons l'ancre dès mon retour.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Capitaine de Maure, que se passe-t-il ? Quelqu'un a-t-il attaqué madame ?";
			link.l1 = "Tu n'aurais pas dû venir ici. Eh bien, Dieu m'est témoin, je ne voulais pas cela.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monsieur, nous avions presque perdu l'espoir de vous voir ici. Je vois la marquise Botot dans votre chaloupe. Je ne vais même pas demander comment cela s'est passé. Votre compagne vous attend. Elle est saine et sauve, prenez-la et fichez le camp d'ici.";
			link.l1 = "S'il vous avez touché à elle, je réduirai votre vieux rafiot en pièces !";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Quelle attention inattendue. Ne t'inquiète pas, elle a été traitée comme une reine prisonnière. Tes menaces ne m'inquiètent pas. Au fait, le Chevalier de Chievous te salue.";
			link.l1 = "Que diable fasse à lui et ses salutations. Où est mon... officier ? Commençons l'échange.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsieur, nous avions presque perdu l'espoir de vous voir ici. Votre compagne vous attend. Elle est saine et sauve... attendez, qui diable est-ce? Où est la marquise?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Votre épée, monsieur. Et pas de plaisanteries, mes gars sont un peu nerveux ces jours-ci. Vous ne voulez pas prendre une balle, n'est-ce pas ?";
			link.l1 = "Tu es sérieux ? Très bien, prends-le, mais sois délicat, ça coûte plus cher que tes quartiers. J'exige une rencontre avec le baronnet Cortney, Votre Excellence !";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Ne t'inquiète pas, je suis sûr qu'il trouvera le temps de te rendre visite.";
			link.l1 = "Quand tu essaies d'aider quelqu'un...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Je n'aime pas ça non plus, Monseigneur. Hélas, ce britannique insolent a une telle autorité que même Monseigneur de Lyon ne peut pas y faire grand-chose. Je m'excuse, Capitaine, veuillez remettre votre épée s'il vous plaît.";
			link.l1 = "J'espere que Monsieur de Chievous ne partagera pas la meme cellule avec moi. Allons-y, messieurs, je suis mort de fatigue. Enfin, un peu de sommeil.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Je ne veux pas paraître impoli, monsieur, mais je n'ai pas le temps de parler maintenant, vous voyez ce qui se passe. Je ne veux rien manquer !";
			link.l1 = "Comme vous voulez, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Ce soir restera dans les annales, je le sens ! Les gens en parleront d'ici jusqu'à Versailles ! Ma Marianne sera ravie et voudra connaître tous les détails. S'il vous plaît, monsieur, écartez-vous, vous bloquez ma vue.";
			link.l1 = "Je pars déjà, monsieur, profitez du spectacle, et dites bonjour à l'inoubliable Marianne... qui qu'elle soit.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah ! Alors, voici monsieur de Maure ! Excusez-moi... capitaine Charles de Maure ! Joignez-vous à moi, je vous prie, voici une magnifique sélection de vins du bon Vieux Monde. Par quoi souhaitez-vous commencer la soirée : il y a une nouveauté - Cabernet Sauvignon des rives de notre bien-aimée Gironde, ou un classique intemporel - Sangiovese italien ?";
			link.l1 = "Merci, monsieur, je boirai avec vous, mais un peu plus tard.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, capitaine de Maure ! Voulez-vous encore un peu de vin... hic ? Regardez ce qu'on vient de nous servir - Syrah de l'année 1643, tout droit des collines du nord de la Vallée du Rhône. C'est, bon sang, une vraie perle ! Et l'année fut excellente à tous égards, je vous le dis... une seule défaite des Espagnols au cap Gat en vaut la peine ! Au fait... pourquoi tout le monde s'agite ainsi, savez-vous ? Quelqu'un se sent mal ? Eh bien - peu importe, à la vôtre...";
			link.l1 = "Eh bien, au moins quelqu'un rend hommage aux douceurs. Adieu, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, capitaine Charles de Maure, j'ai entendu parler de vous, comme tout le monde dans cette ville ! permettez-moi de me présenter - "+GetFullName(npchar)+" ,   vous rencontrer est un grand honneur, croyez-moi ! Êtes-vous vraiment en bons termes avec notre gouverneur ? Pouvez-vous nous présenter ? Je veux lui exprimer mon plus profond respect et...";
			link.l1 = "Peut-être plus tard. Passez une bonne soirée, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, avez-vous vu cela ?! Notre estimé gouverneur et monsieur de Chievous en personne - je pensais qu'ils allaient s'entretuer ici même ! Grandiose ! La marquise Botot s'est surpassée aujourd'hui - tout cela est diablement excitant ! J'attends la suite avec impatience. D'ailleurs, peut-être que le moment est venu ? Vous aviez promis de me présenter... ";
			link.l1 = "Je ne me souviens pas d'avoir promis quoi que ce soit. Je suis désolé, mais je dois y aller.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, vous êtes enfin arrivé au salon de la brillante madame Botot ! Elle a déjà murmuré à quelques reprises qu'elle souhaitait vous voir. Avez-vous réussi à évaluer ses 'pupilles'? Oui, des étoiles comme la marquise ne sont pas pour de simples mortels comme vous et moi. Mais croyez-moi : ces dames sont de véritables œuvres d'art. Peut-être moins étonnantes, mais tout de même - comme Michel-Ange et, disons, Titien.";
			link.l1 = "Une comparaison intéressante, monsieur. Eh bien, je vous laisse profiter de la nuit....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Non, c'est toujours amusant ici, mais maintenant l'air sent clairement un scandale luxueux, tu ne sens pas? Dame Jacqueline m'attend à l'étage, mais je ne peux toujours pas m'éloigner des tables de jeu! Sa Seigneurie et monsieur de Chievous sont des adversaires dignes et extrêmement déterminés. Il semble que les mises aujourd'hui ne voleront pas seulement vers les étoiles, mais briseront le firmament jusqu'aux diables!";
			link.l1 = "Les diables sont en bas, monsieur. Il doit y avoir des anges derrière le firmament du ciel.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Eh bien, au moins une rencontre agréable ! Nous nous sommes déjà rencontrés, capitaine de Maure, mais vous vous en souvenez à peine. "+GetFullName(npchar)+" - J'étais le capitaine de la sixième compagnie d'infanterie de la garnison, j'ai combattu avec vous dans nos rues contre les Espagnols. C'est vrai, j'ai pris une balle dans le genou et pendant la majeure partie de la bataille, j'admirais comment ce même bordel brûlait, tandis que j'étais allongé dans un fossé. Maintenant ici - de nouveau un civil, et de nouveau je l'admire, mais cette fois de l'intérieur.";
			link.l1 = "Heureux de vous rencontrer, monsieur. Ce jour-là était vraiment chaud, mais il faut l'admettre, depuis ce jour, cet endroit est devenu sensiblement plus beau !";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "Et comment trouvez-vous l'atmosphère ici, capitaine ? On dirait que ces bougres de la haute société ont décidé de foutre un sacré bazar ! C'est intéressant, peut-on jouer la chaise du gouverneur comme un pari aux cartes ? Souvenez-vous de mes mots - cela finira par l'acier. C'est dommage, avec mon genou, de tels divertissements ne sont plus pour moi. Cependant, j'ai vu Jacqueline quelque part - son galant est sérieusement passionné par ce qui se passe... Je suppose que je vais tenter ma chance, tant que tout est encore calme ici.";
			link.l1 = "Bonne décision, je vous souhaite du succès, monsieur. Et je dois retourner à... mes clampins.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
