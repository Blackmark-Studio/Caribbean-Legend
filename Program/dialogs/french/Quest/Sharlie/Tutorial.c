void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vous vouliez quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "C’est beau, n’est-ce pas ?";
			link.l1 = "Cette beauté essaie de me tuer depuis deux mois. Sans succès jusqu'à présent.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Tout à fait. Parfois l'océan nous rappelle combien nous sommes petits face à la nature.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "J'ai appris qu'en mer il n'y a que deux états : l'ennui ou la terreur. Ceci... est différent.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "StartSailor_1_fencing":
			dialog.text = "Ha ! Première fois en mer, monsieur ? Quand c'est calme comme ça, n'importe qui peut jouer au capitaine. Profitez-en donc.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, soit dit en passant. Pas 'monsieur', mais monseigneur.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ha ! Première fois en mer, monsieur ? Quand c'est calme comme ça, n'importe qui peut jouer au capitaine. Profitez-en donc.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, soit dit en passant. Pas 'monsieur', mais monseigneur.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ha ! Première fois en mer, monsieur ? Quand c'est calme comme ça, n'importe qui peut jouer au capitaine. Profitez-en donc.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, soit dit en passant. Pas 'monsieur', mais monseigneur.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "Comme vous voudrez, monseigneur. Alors, premier voyage en mer pour vous, seigneur "+pchar.lastname+" ?";
			link.l1 = "Est-ce si évident ? Oui, mon premier voyage. Et je ne suis pas fait pour les cabines exiguës et les biscuits moisis.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Clair comme de l'eau de roche que vous êtes un terrien, monseigneur.";
			link.l1 = "Surveille ta langue ! À un homme d'honneur je jetterais mon gant et exigerais satisfaction. Mais à un rustre comme toi - je couperai simplement les oreilles.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Peut-être à Paris. Mais ici, de tels mots peuvent vous envoyer nourrir les poissons. Je ne brandirai pas cette lame à tout va, monseigneur - et ne faites pas regretter au capitaine de vous laisser marcher armé sur son pont. Le dernier fauteur de troubles, il l'a envoyé à fond de cale - avec des biscuits moisis et de l'eau de cale que même les rats refusaient de boire. Et savez-vous quoi ? Le pauvre bougre a dû payer un supplément quand nous avons atteint le port.";
			link.l1 = "Que peut-on attendre... Bon, oublions ce malentendu. Je dois constamment me rappeler que ce rafiot n'est pas le Louvre.";
			link.l1.go = "StartSailor_5";
		break;
		
		case "StartSailor_5":
			dialog.text = "Hein ? Le Louvre ? Qu'est-ce que c'est censé être ?";
			link.l1 = "Ha ! Le Louvre est un palais pour les élus. Bals, réceptions, intrigues...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "Ah... un bordel alors. On en a plein comme ça. Pas vraiment pour les élus - payez vos pièces et tout est à vous.";
			link.l1 = "Ha ! Tu n'es pas loin de la vérité, matelot.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Moi, c'est Alonso, au fait. Et qu'est-ce qui vous amène au bout du monde, monseigneur ? Vous n'avez sûrement pas traversé l'Atlantique juste pour vous disputer avec un matelot.";
			link.l1 = "Mon père est malade et ne peut quitter notre domaine en Gascogne. J'ai été chargé de retrouver mon... frère aîné. Il est venu ici pour affaires, et on est sans nouvelles de lui depuis longtemps.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Pourquoi ne pas simplement envoyer un homme de confiance, au lieu de souffrir vous-même les affres de la mer ?";
			link.l1 = "La famille passe avant tout. Je ne peux confier son sort au premier venu.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "J'aurais bien aimé - mais selon mon père, c'est à moi de m'en charger. Pourquoi ? Aucune idée.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "Et comment s'appelle votre frère ?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "Et comment s'appelle votre frère ?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper ? Et vous êtes un "+pchar.lastname+" ? Comment ça ?";
			link.l1 = "Ne me regarde pas comme ça. Je suis un fils légitime. Je porte juste le nom de ma mère.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Rien à avoir honte. Vous allez vous intégrer parfaitement – dans le Nouveau Monde, chacun a son histoire. Moi, par exemple...";
			link.l1 = "Je n’ai honte de rien ! Dis-m’en plutôt plus sur la Martinique. C’est une grande ville ? Comme Toulouse ?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "Une ville ? Ha ! La Martinique est une île entière. L'une des plus grandes possessions françaises dans les Caraïbes. On y récolte un café brûlant, on y extrait du soufre infernal et on y met au monde les plus belles femmes du monde. Un excellent mélange, si vous voulez mon avis.";
			link.l1 = "Le café et le soufre ne m’intéressent pas. Mais attends... une île ? Comment vais-je retrouver mon frère sur toute une île ?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Ne vous en faites pas. Saint-Pierre est une petite ville, pas le Louvre bien sûr, mais ce n’est pas non plus la jungle. Mais dans le repaire de bandits qu’est Le François, Dieu nous en garde – un homme de bien n’a rien à y faire.";
			link.l1 = "S’il le faut – j’irai même chez les bandits. Michel m’a toujours sorti des ennuis. À moi de lui rendre la pareille.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Pas mal dit... pour un terrien.";
			link.l1 = "Encore toi ? Combien de temps avant cette fichue Martinique ?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Cinq jours.";
			link.l1 = "Cinq ?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "Au minimum. Et si les pirates attaquent, on n'y arrivera peut-être même pas. Les Petites Antilles sont dangereuses, même sans cargaison précieuse à bord.";
			link.l1 = "À part les passagers !";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ha-ha ! Ne vous inquiétez pas. Au pire, je vous cacherai personnellement dans la cale – aucun pirate ne pensera à chercher un noble gascon parmi les barils de rhum ! On n’est pas stupides quand même – mélanger un Gascon vivant et du rhum ? Ça ferait une explosion pire que de la poudre, ha-ha !";
			link.l1 = "Ha ! Heureusement que le rhum est épuisé depuis un mois !";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "Euh... ce genre de choses, vaut mieux ne pas les dire à haute voix. Les gens pourraient croire que vous êtes responsable de notre manque de rhum.";
			link.l1 = "D’accord, Alonso, je ne dirai rien. De toute façon, je ne boirai jamais ce poison. Et quant à ton génial plan de m’envoyer à la cale avant le combat – tu peux rêver.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Et pourquoi donc ?";
			link.l1 = "Je suis un noble, je manie l'épée avec assurance et je ne vais pas me terrer dans la cale.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "S’il y a du grabuge – je défendrai le navire et me battrai avec les autres. Comment faire autrement ?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Je suis capable de décider moi-même quand me battre et quand fuir. On verra bien.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Peut-être que vous avez quelque chose en vous. Mais attention – les Caraïbes adorent dépouiller ceux qui y arrivent le nez en l’air. Vous ne survivrez pas à une rencontre avec l'avant-garde des pirates. Le premier va-nu-pieds à la sortie de Saint-Pierre vous tranchera la gorge.";
			link.l1 = "Tu ne me connais pas du tout.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ha. Peut-être que vous avez quelque chose en vous. Mais attention – les Caraïbes adorent dépouiller ceux qui y arrivent le nez en l’air. Vous ne survivrez pas à une rencontre avec l'avant-garde des pirates. Le premier va-nu-pieds à la sortie de Saint-Pierre vous tranchera la gorge.";
			link.l1 = "Tu ne me connais pas du tout.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ha. Peut-être que vous avez quelque chose en vous. Mais attention – les Caraïbes adorent dépouiller ceux qui y arrivent le nez en l’air. Vous ne survivrez pas à une rencontre avec l'avant-garde des pirates. Le premier va-nu-pieds à la sortie de Saint-Pierre vous tranchera la gorge.";
			link.l1 = "Tu ne me connais pas du tout.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "Mais moi, je connais le Nouveau Monde et ses habitants. Si vous ne comptez pas dépérir derrière des livres de comptes ou servir dans la maison d’un gouverneur – il faudra tout apprendre depuis le début.";
			link.l1 = "Heureusement, je ne compte pas m'attarder ici.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "C’est ce que vous croyez. Nous ramenons rarement des passagers en Europe. Certains meurent – de fièvre, de corde ou de balle. D'autres restent – pour toujours. J'ai vu de frêles aristocrates devenir capitaines, et de grands brigands devenir des planteurs respectés. Et aussi – de brillants officiers tomber dans la misère et devenir des vagabonds.";
			link.l1 = "C’est tentant, sacré nom, mais je rentrerai en France. On m’y attend.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ah oui, c’est vrai. Le père malade ?";
			link.l1 = "Disons plutôt... qu'il y a une dame dont le mari ne tient pas vraiment à me voir à Paris. Mais quelques mois passeront, et la tempête se calmera.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha ! Alors vous êtes bien au bon endroit. Les Caraïbes sont un paradis pour ceux qui fuient les maris jaloux. Et le temps ici passe sans qu’on s’en rende compte. Donnez-vous du temps – vous finirez marin, vous verrez !";
			link.l1 = "Plutôt capitaine. Je ne suis pas fait pour être simple matelot. Je suis peu doué pour le travail manuel.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "En France, les hommes gouvernent par droit de naissance, mais à bord, c’est le capitaine : roi, juge et Dieu. Et nul ne sait ce qu’il a dû traverser pour obtenir son chapeau de capitaine. Ici, chacun reçoit ce qu’il mérite. Comme on dit sur notre pont – à chacun son dû.";
			link.l1 = "Quelle absurdité. À propos de capitaines – il me faut parler au vôtre, surtout qu’il me cherche. À bientôt, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Vous vouliez me demander quelque chose ?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Je viens de la part de monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Rien.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Bah ! Notre binoclard vous a embarqué aussi ?";
			link.l1 = "Binoclard ?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Vous avez vu ses lunettes ? Voilà ! Mais ne vous y trompez pas : l’équipage respecte monsieur Pinchon. On apprécie toujours les bons médecins à bord. Et comme trésorier, il est pas mal non plus.";
			link.l1 = "Qu’est-ce que vous avez à faire avec lui ?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Euh... Excusez-moi, mais c’est une affaire interne. Ne vous inquiétez pas, on enfreint pas les lois du navire.";
			link.l1 = "Et les lois normales ?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "Celles-là, on s’en moque. Alors, combien je dois ?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 doublons.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 doublons.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 doublons.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Je dois tout revérifier. Je reviendrai plus tard.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Voilà l’or, enfin ! Tiens-toi prêt, Saint-Pierre ! Ha-ha !";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Voilà l’or, enfin ! Tiens-toi prêt, Saint-Pierre ! Ha-ha !";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Voilà l’or, enfin ! Tiens-toi prêt, Saint-Pierre ! Ha-ha !";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, "+pchar.name+". Vous n’étiez pas pressé, on dirait. Quand le capitaine d’un navire souhaite vous parler, vous devez vous présenter immédiatement. Auriez-vous un problème avec l’autorité ?";
			link.l1 = "Je ne suis pas habitué à recevoir des ordres, capitaine.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Excusez-moi, capitaine, j’ai été retenu.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "On m’a déjà fait comprendre que sur ce navire, c’est vous qui faites les règles.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (passer le tutoriel et commencer le jeu en Martinique)";
				link.l9.go = "BetaTest_StartGame";
			}
			//NextDiag.TempNode = "Captain";
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "Je ne tolérerai aucune remise en question de mon autorité. Vous n’imaginez pas combien de passagers ont des accidents malheureux en mer. Vous avez une chance inouïe que j’aie intérêt à vous livrer entier à Saint-Pierre.";
			link.l1 = "Qu’est-ce que vous voulez dire ?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Excuses acceptées. Profitez-en. Vous ne verrez pas de sitôt un autre coucher de soleil comme celui-ci.";
			link.l1 = "Qu’est-ce que vous voulez dire ?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Heureusement que vous avez au moins appris quelque chose pendant ce voyage. Le pouvoir d’un capitaine est absolu – et parfois il s’étend même à la terre ferme, loin du navire.";
			link.l1 = "Qu’est-ce que vous voulez dire ?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Capitaine. Veuillez vous adresser à moi selon le règlement naval.";
			link.l1 = "Qu’est-ce que vous voulez dire, capitaine ?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "Je voulais vous informer que nous avons affalé les voiles et dérivons. Malheureusement, votre arrivée en Martinique sera retardée de quelques jours.";
			link.l1 = "Mais pourquoi, capitaine ?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Parce que c’est ma décision.";
			link.l1 = "Est-ce que cela a un rapport avec notre rencontre d’hier avec ce convoi marchand en route pour... euh, comment ça s’appelait déjà ?";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Écoutez-moi bien, "+pchar.name+" : j’ai une conversation sérieuse à avoir avec vous. Je vous invite à dîner dans ma cabine. Les cloches vont bientôt sonner, et nous pourrons passer un moment civilisé – en vidant la dernière bouteille de vin à bord.";
			link.l1 = "Merci pour l’invitation. Ce sera un honneur, capitaine.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Prévenez-moi quand vous serez prêt. Nous avons encore du temps, alors vous êtes libre de vous promener sur le navire – à condition de ne pas distraire mes hommes de leur travail.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "D’autres questions ?";
			link.l1 = "(Terminer les affaires) Je suis prêt, capitaine. Avec vous – je boirai même du Bourgogne !";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Que regardez-vous donc dans cette longue-vue... capitaine ?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Capitaine, j’ai eu le plaisir de parler avec un certain Alonso. Quel est son poste à bord ?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Capitaine, parlez-moi de votre navire. Une pinasse, n’est-ce pas ?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "À bientôt, capitaine.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Rien de particulier, j’observe simplement l’horizon. Le navire est à la dérive — nous sommes une cible facile.";
			link.l1 = "Vous cherchez des pirates ?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Ou des Espagnols. Nous naviguons sous pavillon français et sans escorte, et les Petites Antilles sont un vrai carrefour — le domaine de Jacques Barbazon.";
			link.l1 = "C’est qui ? Un gouverneur ?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Pire — un des barons pirates. Ces pendards ont fondé une sorte d’organisation appelée la Fraternité des Côtes. Ils ont divisé les Caraïbes en six zones et placé un baron sur chacune pour éviter les conflits internes.";
			link.l1 = "Pourquoi les autorités ne font-elles rien ?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "Vous êtes bien naïf, "+pchar.name+". La piraterie n’existe que parce que les autorités locales permettent aux pirates de réparer et ravitailler leurs navires dans certains ports — en échange d’une part importante du butin. Cela me déplaît de le dire, mais les seuls à faire quelque chose contre cette peste noire, ce sont les Espagnols. Sans eux, il ne nous resterait qu’à couvrir le navire de canons coûteux et à embaucher une escorte.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "Matelot supérieur. Je ne sais pas grand-chose de lui, mais je peux vous dire une chose : si chaque homme cache un squelette dans son placard, Alonso, lui, a tout un cimetière.";
			link.l1 = "On dirait que vous ne lui faites pas confiance.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
		case "Captain_7_question_2_2":
			dialog.text = "Pas du tout. Vous croyez qu’il est facile de trouver des marins expérimentés ? Il faut au moins un an et un excellent bosco pour que la racaille recrutée dans les tavernes commence à ressembler à un équipage. De plus, Alonso est la voix de l’équipage. Le capitaine ne se mêle pas aux gens du commun, mais il serait idiot – et même mortel – d’ignorer que les simples matelots ont leurs propres intérêts. C’est lui qui les défend, quand il le faut.";
			link.l1 = "Et que se passe-t-il si l’équipage est mécontent ?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "On me pendra, et vous – on vous égorgera. Ne tremblez pas ainsi. Tant que l’équipage reçoit sa solde, du rhum, des vivres et des soins – le contrat entre le capitaine et l’équipage est respecté. Je n’envoie pas mes hommes au casse-pipe pour rien, je ne punis pas par caprice, je partage le butin et parfois j’offre une tournée ou quelques plaisirs à terre. Ainsi l’équilibre fragile est préservé et le navire atteint toujours sa destination.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Vous touchez une corde sensible, "+pchar.name+" ! Je pourrais parler de ma belle pendant des heures. Troisième classes, vingt canons, excellente vitesse – ne vous fiez pas à l’étiquette 'marchand' !";
			link.l1 = "J’ai bien compris pour les canons et la vitesse. Mais le 'classe' ? Et 'marchand' ?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "Les classes sont une classification conditionnelle des navires selon leur nombre de canons. Le septième classe est à peine plus qu’une chaloupe, et le premier est presque une forteresse. Mais ne répétez surtout pas cela en Europe, surtout devant des officiers de marine.";
			link.l1 = "Pourquoi ? C’est une blague de marins ?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "On vous prendra pour un ignorant complet et on se moquera de vous. Honnêtement, dans une flotte sérieuse, les classes sont utilisés uniquement pour les navires de guerre et ne fonctionnent pas de cette manière. Mais dans les Caraïbes, comme d’habitude, c’est différent.";
			link.l1 = "Et que vouliez-vous dire en appelant votre navire un 'marchand' ?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Encore une convention. Les navires de guerre sont plus solides et meilleurs au tir, les raiders pillent et s’enfuient. Les marchands peuvent transporter beaucoup de marchandises, de marins ou de canons – mais il faut faire un choix au détriment du reste, sinon leur vitesse devient risible. Il existe aussi des navires polyvalents, mais il n’y a pas grand-chose à dire sur eux – ils s’adaptent aux besoins de leur propriétaire.";
			link.l1 = "Vous avez l’air tout excité, capitaine.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "J’aime mon navire, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Eh bien, vous avez de la chance – il ne me reste plus que du Bourgogne... Attendez une seconde, "+pchar.name+". D’où vous vient mon ancien chapeau ?!\nUn instant. Hé, dans la mâture ! Qu’est-ce qu’il se passe là-haut ?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Eh bien, vous avez de la chance – il ne me reste plus que du Bourgogne.\nUn instant. Hé, dans la mâture ! Qu’est-ce qu’il se passe là-haut ?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Désolé, monsieur "+pchar.lastname+", mais l’accès vous est interdit.";
			link.l1 = "Je suis autorisé à entrer dans la cabine du capitaine. Vous devriez le savoir maintenant.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Quel dommage, mon plan sournois a échoué. À bientôt, matelot.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Désolé, monsieur, mais les circonstances ont changé.";
			link.l1 = "Et que s’est-il passé, au juste ?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "Le voyage touche à sa fin, et le capitaine ne veut pas qu’on vide sa cabine avant que quelqu’un ne file vers les bandits de Le François à l’arrivée.";
			link.l1 = "Je doute que le capitaine pensait à moi en donnant cet ordre.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Eh bien... vous avez raison. Et vous avez déjà partagé plusieurs repas dans la cabine du capitaine. Passez, monsieur "+pchar.lastname+".";
					link.l1 = "C’est mieux ainsi.";
					link.l1.go = "OhrannikCabin_4";
					notification("Vérification réussie", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Insi... insi-quoi ? Je ne voulais pas dire ça, monsieur "+pchar.lastname+" !";
					link.l1 = "Alors tu dois me laisser passer.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Monsieur, vous comprenez bien que la cabine du capitaine n’est pas un moulin. Et ici, les ordres sont respectés à la lettre.";
					link.l1 = "Par tous les diables, j’ai hâte de poser pied à terre. C’est humiliant !";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Monsieur, nous en avons déjà parlé. Je ne peux pas vous laisser passer.";
					link.l1 = "Tu es têtu, matelot. À plus.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Compétence insuffisante (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Eh bien... bon, je suppose que ça ne causera pas de gros problèmes.";
			link.l1 = "Voilà qui est mieux !";
			link.l1.go = "OhrannikCabin_4";
			notification("Vérification réussie", SKILL_Leadership);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Encore quelque chose, monsieur ? Je ne peux pas vous laisser passer – le capitaine craint pour ses biens.";
			link.l1 = "Que voulez-vous dire, matelot ? Vous m’accusez de vol ? Faites attention à vos paroles. C’est de la pure insinuation !";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Rien du tout, matelot.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Hé, espèce d’andouille enrubannée ! T’as mis le diable dans le guindeau ou quoi ?!\nT’as fait sauter la sécurité avec ton pied royal ! Tu veux nous envoyer tous par le fond ?!\nFais-nous plaisir : ne touche à rien, sauf si c’est pour nous filer ton rhume français !";
			link.l1 = "Et c’est quoi, au juste ?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "C’est le guindeau, abruti. Il remonte l’ancre. Si tu ne le bloques pas – il va arracher le navire ou enrouler quelqu’un comme un hareng dans un tonneau !";
			link.l1 = "Ha... Et dans l’autre sens – il descend l’ancre, c’est ça ?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "Non, malin, là il remonte le temps. Sauf que toi, t’as pas de bol – t’es déjà né !";
			link.l1 = "Bon, personne n’a été blessé – pas vrai ? Sacré machin, un navire. Je ferai plus attention.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Vous regardez ce long canon avec autant d’admiration que vous contempliez le coucher de soleil tout à l’heure.";
			link.l1 = "Tu m’observes beaucoup, on dirait, Alonso. Parle-moi donc de cette merveille d’ingénierie militaire.";
			link.l1.go = "SailorWithCannon_2";
		break;
		
		case "SailorWithCannon_2":
			dialog.text = "C’est un canon de seize livres. On n’en trouve pas sur tous les navires de guerre.";
			link.l1 = "Et c’est facile de viser avec ?";
			link.l1.go = "SailorWithCannon_3";
		break;
		
		case "SailorWithCannon_3":
			dialog.text = "À bout portant, on explose n’importe qui. Cent yards – et on est dans le feu de l’action. Plus loin ? Du bruit et des flammes, mais c’est déjà ça.";
			link.l1 = "Cent yards – et l’ennemi peut en faire autant.";
			link.l1.go = "SailorWithCannon_4";
		break;
		
		case "SailorWithCannon_4":
			dialog.text = "Exact. Tout dépend alors de l’équipage et des canonniers. Dommage que notre canonnier dorme – il vous aurait tout expliqué, puis vous aurait chargé dans le canon, ha ha !";
			link.l1 = "Le canonnier, c’est un officier, non ?";
			link.l1.go = "SailorWithCannon_5";
		break;
		
		case "SailorWithCannon_5":
			dialog.text = "En général, oui. Sans un bon canonnier, mieux vaut éviter la bataille – autant jeter les canons par-dessus bord et fuir.\nLes capitaines marchands n’emportent rarement plus que des six livres – ils comptent sur une escorte ou la chance.\nC’est logique : sans canons lourds ni munitions, le navire file plus vite et on peut charger plus de marchandises.\nSi notre capitaine ne s’était pas ruiné pour ces beautés, on aurait encore du rhum... Ah !";
			link.l1 = "Et le capitaine ne dirige pas le tir lui-même ?";
			link.l1.go = "SailorWithCannon_6";
		break;
		
		case "SailorWithCannon_6":
			dialog.text = "Avec un bon canonnier et un équipage rodé, il n’en a pas besoin. Mais si le capitaine vise lui-même, au lieu de crier “Feu !” depuis la dunette – les trous dans les coques ennemies se multiplient.";
			link.l1 = "Je peux tirer ?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Merci pour cette leçon, Alonso. Tu es une véritable encyclopédie navale.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Évidemment ! Mais touchez pas au canon, hein, et ne stressez pas l’équipage.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;
		
		case "SailorWithCannon_7":
			dialog.text = "Tirer ? Peu probable. Mais déclencher le coup de feu ? Faut demander au capitaine. J’lui demande !";
			link.l1 = "Non, non, c’est pas la peine !";
			link.l1.go = "SailorWithCannon_8";
		break;
		
		case "SailorWithCannon_8":
			dialog.text = "Caaap’taiiine !";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "Que se passe-t-il ici, Alonso ?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;
		
		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\\Sharlie\\Tutorial.c");
		break;
		
		case "CaptainWithCannon_3":
			dialog.text = "Monsieur "+pchar.name+" propose de tirer au canon — uniquement à des fins d’entraînement.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Je croyais que tu défendais les intérêts de l’équipage, Alonso. Et voilà que tu proposes de réveiller la prochaine veille et d’alarmer tout le monde de la manière la plus barbare ?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\\Sharlie\\Tutorial.c");
		break;
		
		case "CaptainWithCannon_7":
			dialog.text = "Je pense qu’on ferait bien de les faire bouger un peu. Je n’aime pas que nous soyons en dérive à la vue de tous. Mieux vaut prévenir que guérir.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\\Sharlie\\Tutorial.c");
		break;
		
		case "CaptainWithCannon_9":
			dialog.text = "Ne porte pas malheur !... Bon. Un seul tir. À blanc.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_10":
			dialog.text = "Amusez-vous bien, "+pchar.name+". On réveillera l’équipage... à vos frais, ha ha !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Auriez-vous une minute, monsieur ?";
			link.l1 = "Parle, matelot.";
			link.l1.go = "SailorWantRum_1";
		break;
		
		case "SailorWantRum_1":
			dialog.text = "Enchanté, monsieur. Je m'appelle Henry. Ça vous dirait de gagner un peu d’argent ?";
			link.l1 = "Un peu — c’est combien ?";
			link.l1.go = "SailorWantRum_2";
		break;
		
		case "SailorWantRum_2":
			dialog.text = "Cinq cents pesos.";
			link.l1 = "Combien ?! Et que veux-tu que je fasse pour cette somme ? J’espère que ce n’est pas pour fomenter une mutinerie ?";
			link.l1.go = "SailorWantRum_3";
		break;
		
		case "SailorWantRum_3":
			dialog.text = "Mon Dieu, monsieur ! Pourquoi crier ainsi ?";
			link.l1 = "C’est une belle somme, matelot. Même à Paris, on peut vivre un moment avec ça.";
			link.l1.go = "SailorWantRum_4";
		break;
		
		case "SailorWantRum_4":
			dialog.text = "Eh bien, je ne vais pas profiter de votre ignorance et je vais être franc : aux Caraïbes, cinq cents pesos — ce n’est rien. Les capitaines et les marchands amènent tellement de marchandises que les prix grimpent pour tout ce qui a la moindre utilité. C’est parfois risible : une lame rare peut coûter autant qu’un petit navire.";
			link.l1 = "C’est de la folie.";
			link.l1.go = "SailorWantRum_5";
		break;
		
		case "SailorWantRum_5":
			dialog.text = "Que voulez-vous ? Nous espérons tous que les choses se stabiliseront et que les prix reviendront à la normale. Alors, intéressé par cinq cents pesos ?";
			link.l1 = "D’abord, je veux entendre les détails.";
			link.l1.go = "SailorWantRum_6";
		break;
		
		case "SailorWantRum_6":
			dialog.text = "Vous savez sans doute que la situation avec le rhum à bord est critique. Pourtant, je suis persuadé qu’il reste quelques bouteilles. Le rhum en bouteille — ce n’est pas de la piquette en barrique. Excellent goût, évite les empoisonnements, renforce le bras et la santé — en somme, une denrée précieuse. Surtout à la fin du voyage, quand l’horizon vous rend fou.";
			link.l1 = "Et qu’en feras-tu ? Et pourquoi ne cherches-tu pas toi-même ?";
			link.l1.go = "SailorWantRum_7";
		break;
		
				case "SailorWantRum_7":
			dialog.text = "Quand aurais-je le temps ? On est en sous-effectif, on bosse pour trois. Et le rhum, je vais le revendre — je trouverai bien preneur.";
			link.l1 = "J’apprécie la franchise, matelot.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "Alors, vous acceptez ? Il me faudrait trois bouteilles.";
			link.l1 = "Je vais essayer, mais je ne promets rien.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Je préfère refuser. Ce genre de travail ne me convient pas.";
			link.l2.go = "SailorWantRum_10";
		break;
		
		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;
		
		case "SailorWantRum_10":
			dialog.text = "Dommage, mais je ne vous en veux pas. Passez une bonne soirée, monsieur.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;
		
		case "SailorWantRum_PrinestiRum":
			dialog.text = "Oui, monsieur "+pchar.lastname+" ?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Voici tes trois bouteilles de rhum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, j’ai quelque chose pour toi de la part de monsieur Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Rien.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Toujours heureux de rendre service ! Combien me revient-il cette fois ?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 doublons.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 doublons.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 doublons.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Je dois tout revérifier. Je reviendrai plus tard.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;
		
		case "RumGold_DatDeneg_gold28":
			dialog.text = "Merci, monsieur "+pchar.lastname+". Transmettez mes salutations au trésorier.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold35":
			dialog.text = "Merci, monsieur "+pchar.lastname+". Transmettez mes salutations au trésorier.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Merci, monsieur "+pchar.lastname+". Transmettez mes salutations au trésorier.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Merci, monsieur "+pchar.lastname+". Vous avez fait ça avec adresse !";
			link.l1 = "J’espère recevoir mon paiement avec autant d’adresse.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Peut-être préférez-vous un paiement en nature ?";
			link.l1 = "Je vois que vous n’êtes pas si honnête que ça.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Mais non ! Si vous choisissez l’argent, vous l’aurez ! Je voulais juste dire que je peux aussi partager mes connaissances.";
			link.l1 = "De quel genre de connaissances s’agit-il ?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Je peux vous apprendre beaucoup sur la navigation. Des choses qu’on ne trouve pas dans les livres.";
			link.l1 = "Très bien, donne-moi la leçon la plus chère de ma vie.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Cinq cents conseils ne valent pas cinq cents pièces. Je prends l’argent.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Avec plaisir, monsieur "+pchar.lastname+". Et encore merci !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;

		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "J’espère vraiment, monsieur "+pchar.name+", que ma leçon vous sera utile. Savez-vous ce qu’est la navigation ?";
			link.l1 = "Tu vas être surpris, mais oui. Je sais lire aussi. La navigation, c’est déterminer une position et calculer une trajectoire, comme celle d’un navire.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;
		
		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ah, vous parlez des étoiles et des cartes. Non, ce n’est pas mon domaine. Il faut demander au navigateur ou au capitaine. Chez nous, la ‘navigation’ désigne plutôt la capacité à manœuvrer et commander un navire.";
			link.l1 = "Chez ‘vous’ ?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "Aux Caraïbes. C’est comme ça ici, ne me demandez pas pourquoi. Bref : plus vous êtes bon en navigation, plus vous pouvez tirer de vitesse et de manœuvrabilité du navire. L’équipage réagit plus vite aux ordres de voile. Mais ce n’est pas le plus important.";
			link.l1 = "Tu sais bien entretenir le suspense.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Plus vos compétences en navigation sont élevées, plus vous pouvez commander de gros navires ! Et si vous prenez un navire au-delà de vos capacités, vous perdrez en concentration, en force, voire en santé !";
			link.l1 = "Ça a l’air dangereux. Étonnant que j’aie survécu jusque-là.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Heureusement, il n’est pas nécessaire d’être expert en tout. Vous pouvez toujours engager un bon navigateur, il couvrira vos lacunes. Assurez-vous simplement qu’il soit payé à temps et vous soit loyal. Être sans navigateur sur un navire que vous ne pouvez pas contrôler... c’est peu recommandable.";
			link.l1 = "Merci pour la leçon, Henry. Je ne sais pas si cela me servira, mais un savoir de plus ne fait jamais de mal.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Avec plaisir, monsieur "+pchar.lastname+". Et encore merci !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(chante) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Que fais-tu ici, matelot ?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;

		case "OldSailor_1":
			dialog.text = "Moi, je suis comme madame Michel — je cherche un chat. Mais je ne crie pas — elle n’aime pas ça.";
			link.l1 = "Je l’ai vue ce matin — elle a encore griffé mes bottes.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Ce n’est rien. Les bottes du capitaine n’ont pas eu autant de chance. Tu aimes les chats ?";
			link.l1 = "Bien sûr que j’aime.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Pas trop.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Ça se comprend. Comment écraser ces maudits rats sinon ?";
			link.l1 = "Mais vous ne pouvez pas toujours compter sur les chats ? Ce sont des créatures très capricieuses.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Tu as tort. Les chats sont aimés et appréciés à bord. Comment écraser ces maudits rats sinon ?";
			link.l1 = "Mais vous ne pouvez pas toujours compter sur les chats ? Ce sont des créatures très capricieuses.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "OldSailor_5":
			dialog.text = "C’est vrai. C’est pourquoi on doit compter sur l’arsenic. Mais essayez donc d’en trouver aux Caraïbes. Et voilà qu’on perd de la marchandise — les rats souillent le rhum, abîment les biscuits secs et rongent tout le reste.\nEt notre trésorier dit : «Prenez-le comme une taxe sur le commerce».\nMais nous savons bien : il est juste paresseux, voilà tout. Sans notre chère Chantal, le capitaine l’aurait déjà envoyé vivre dans la cale pour attraper les rats lui-même, ha-ha !";
			link.l1 = "Bonne chance avec ton chat. Je dois y aller.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Attendez, monsieur. Normalement, un simple matelot ne voit les passagers nobles que sur le pont, et vous — vous êtes descendu dans la cale !";
			link.l1 = "La curiosité a tué le chat, ha-ha !";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Vous vous intéressez à la mer ?";
			link.l1 = "On dirait que chaque membre de l’équipage s’est donné pour mission de faire de moi un vrai marin.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Rien d’étonnant. Même si la mer nous a apporté bien des malheurs, nous aimons notre métier. Et un marin apprécie toujours qu’un nouveau montre un véritable intérêt.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;

		case "OldSailor_9":
			dialog.text = "Alors, dites-moi : quelle est la compétence la plus importante pour un capitaine ?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "La navigation. Elle détermine la taille du navire qu’il peut commander.";
				link.l1.go = "OldSailor_10";
				notification("Test réussi", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Je ne vais pas mentir, je ne sais pas.";
				link.l1.go = "OldSailor_9_1";
				notification("Compétence insuffisante (6)", SKILL_Sailing);
			}
		break;
		
		case "OldSailor_9_1":
			dialog.text = "Ne vous découragez pas, monsieur. Parlez à l’équipage, promenez-vous sur le navire. Si vous trouvez la réponse, je vous raconterai quelque chose de très curieux. Comme à un des nôtres.";
			link.l1 = "Je m’en souviendrai. À la prochaine !";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Exact ! Et maintenant une autre question piège : que vaut-il mieux avoir — des voiles carrées ou des voiles obliques ?";
			link.l1 = "Difficile à dire, mais je me doute qu’il y a un piège. Je dirais que tout a son utilité.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Encore une bonne réponse ! Les voiles carrées sont puissantes quand le vent pousse. Mais les voiliers à voiles obliques peuvent tirer des bords et progresser même contre le vent. Ça fait plaisir de voir que vous n’avez pas perdu votre temps, monsieur.";
			link.l1 = "Je ne suis pas sûr que ce savoir me serve un jour... Sauf peut-être pour impressionner les dames de la haute société en jouant les marins chevronnés, ha-ha !";
			link.l1.go = "OldSailor_12";
		break;

		case "OldSailor_12":
			dialog.text = "Oh, je ne sais pas, monsieur "+pchar.name+". Peut-être êtes-vous un noble — mais vous vous comportez comme l’un des nôtres. Et on apprécie ça. Le capitaine prépare quelque chose. Il y a eu de l’eau dans le gaz entre vous.";
			link.l1 = "Des bêtises. Qu’insinues-tu, matelot ?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "On dit qu’il n’a pas envoyé cette lettre à Capsterville pour rien, il y a quelques jours, avec un navire de passage.\nEt qu’il est passé en dérive — juste à la fin du voyage, quand tout le monde crie de rentrer à terre au plus vite.";
			link.l1 = "Je ne me soucie pas des rumeurs. Pourquoi faire ? Je peux simplement lui poser la question. Il ne refusera pas une réponse honnête à un noble.";
			link.l1.go = "OldSailor_14";
		break;
		
		case "OldSailor_14":
			dialog.text = "Vous ne le connaissez pas, monsieur "+pchar.name+". Il refusera — et pas qu’un peu. En plus, il est furieux — il a perdu sa clé.";
			link.l1 = "Une clé ?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "De son coffre, dans sa cabine. Je pense qu’elle ne doit pas être bien loin. Elle traîne quelque part, c’est sûr.";
			link.l1 = "Trouver la clé ? Moi ?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "C’est vous qui voyez.\nAu fait, monsieur "+pchar.name+", vous n’auriez pas encore un peu de rhum ? Vous n’avez pas tout donné à Henry, ha-ha !";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Oui. Tiens.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Malheureusement, non. C’est un miracle que j’aie trouvé ces trois bouteilles.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "C’est vrai. Bonne chance, monsieur "+pchar.name+". Moi, je pars à la recherche de cette petite coquine rayée.";
			link.l1 = "Bonne chance à toi aussi, matelot.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Ah, vous m’avez bien aidé ! Vous vous êtes bien comporté avec l’équipage, monsieur "+pchar.name+". Voici un petit cadeau — pour vous porter chance !";
			link.l1 = "Une pierre trouée ? Comme c’est charmant.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Riez tant que vous voulez. Mais moi je vous le dis : en mer, un talisman, ça peut pas faire de mal.";
			link.l1 = "Vous êtes un peuple bien superstitieux, les marins. Bonne chance à toi, matelot.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Vous avez trouvé la réponse ? Quelle est la compétence la plus importante pour un capitaine ?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "La navigation. Elle détermine la taille du navire qu’il peut commander.";
				link.l1.go = "OldSailor_10";
				notification("Test réussi", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Pas encore.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Compétence insuffisante (6)", SKILL_Sailing);
			}
		break;
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Hé, fiston !";
			link.l1 = "Tu ne ressembles pas à mon père. Et tant mieux.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha ! Moi, je serais fier d’avoir un fils aussi grand et noble. Seul un vrai dur comme moi peut engendrer un tel fils.";
			link.l1 = "Bon, je prends le compliment. Que se passe-t-il ?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Un peu d’aide humaine me ferait pas de mal, fiston. On m’a dit de préparer les boulets aux canons — on ne sait jamais dans ces eaux dangereuses. J’en ai porté la moitié depuis la cale, mais mon dos a lâché sur la dernière caisse.";
			link.l1 = "Pourquoi tu ne demandes pas de l’aide à tes camarades ? Je croyais que les marins s’entraidaient.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Ce que nos gars détestent le plus, c’est bien de trimballer des charges lourdes sans nécessité. C’est mon sort aujourd’hui — porter des caisses de boulets depuis la cale. Une sale besogne, indigne d’un marin comme moi. Mais bon, que faire ?";
			link.l1 = "Ne te plains pas autant. Je vais t’aider. Au moins, je verrai enfin cette cale dont on me parle comme d’un monstre.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Athlète) Tu vois mon sabre ? Il pèse plus que toi. Je vais chercher tes boulets, c’est rien pour moi.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Je ne fais pas de travail manuel, matelot. Débrouille-toi avec tes caisses.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Merci, fiston. Mais ne te casse pas le dos !";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ждёт ядра
			dialog.text = "Comment ça va, fiston ?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Tiens, tes boulets. Je m’attendais à ce qu’ils soient plus gros.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Ton nom, c’est bien Paul ?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "À plus.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Э-э-э. Ну д-да.";
			link.l1 = "Твоё имя есть в списке, который мне дал месье Пиншон.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Toujours heureux de rendre service ! Qu’est-ce qui m’est dû cette fois ?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 doublons.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 doublons.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 doublons.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Je dois tout revérifier. Je reviendrai plus tard.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Merci, fiston.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Merci, fiston.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Merci, fiston.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Pas besoin de plus gros ! Il ne manquerait plus qu’un pareil cadeau touche la coque — et il pourrait bien rebondir partout sur le pont comme une balle si ça transperce la poupe !";
			link.l1 = "Tu as déjà vu ça ?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;

		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Ça m’est arrivé, fiston. L’homme sait bien inventer des armes mortelles. Prenons la mitraille — ça ne va pas loin, ça n’endommage pas la coque, mais ça peut envoyer une douzaine de gars ad patres. Ou le boulet ramé — si tu touches les voiles, ça les réduit en lambeaux ! Et les bombes ? J’en ai jamais vu, et tant mieux ! Invention du diable. Et puis ça coûte cher.";
			link.l1 = "J’ai déjà pu constater la puissance de feu des boulets — sur ton pauvre dos.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Tu m’as bien aidé, fiston. Et je n’oublie pas. Tiens — une bouteille de rhum de première qualité, presque pleine, ha-ha !";
			link.l1 = "Où l’as-tu trouvée ? Tout le monde dit que le rhum a disparu bien trop tôt à bord. Avec ça, tu aurais pu convaincre n’importe quel membre de l’équipage de te porter toutes les caisses depuis la cale.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "C’est comme ça, fiston. Merci à toi et à la prochaine.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Si vous comptiez dormir — manque de chance. Notre canonnier a pris votre couchette. Et vous savez bien que le réveiller est impossible.";
			link.l1 = "Quand il veut, il entend très bien !";
			link.l1.go = "OfficerTorgovets_1";
		break;

		case "OfficerTorgovets_1":
			dialog.text = "C’est encore rien. On dit que l’équipage de Sharp avait un canonnier aveugle. Il visait au son du canon.";
			link.l1 = "Vous êtes bien bavard ce soir, monsieur le bosco.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "Et pour cause ! On sera bientôt à terre, et c’est le moment de transformer la camelote restante en jolis pesos. Le bordel de Saint-Pierre les accueille toujours avec joie, ha-ha !";
			link.l1 = "Étonnant que ce soit vous, et non le trésorier, qui vous occupiez du petit commerce à bord.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "Il ne sait pas parler aux gens ! C’est pour ça qu’il y a un bosco — qui sait manier la parole et l’action, ha-ha. Le trésorier a aussi ses petites affaires — mais je ne me mouille pas dans ces eaux troubles.";
			link.l1 = "Et qu’avez-vous à vendre aujourd’hui ?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "La dernière bouteille de rhum du navire, quelques amulettes utiles... et voilà ! Une carte au trésor complète.";
				link.l1 = "Vous devriez être marchand au lieu de bosco ! Montrez-moi ça.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Quelque chose d’autre ?";
				link.l1 = "Montrez-moi ce que vous avez.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Des amulettes ? Comme celle qui pend à votre cou ?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Pardon... Une carte au trésor ?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Peut-être une autre fois.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, un œil de lynx, monsieur. Oui, la “Tête de corail” est bien utile. Surtout pour moi. Si jamais, que Dieu m’en garde, je dois mener un abordage — avec ça, mes hommes se rangent en un clin d’œil.";
			link.l1 = "Vous y croyez vraiment ?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Je n’ai pas besoin d’y croire. C’est la règle dans les Caraïbes et le lot des marins. Les amulettes sont utiles. Alors si vous restez ici quelque temps, je vous conseille d’en avoir quelques-unes sur vous — pour toutes les occasions.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Oh oui. Dans les Caraïbes, ce n’est pas rare. Certains ont de la chance — ils touchent le gros lot. Ensuite, deux options : payer des taxes, vivre calmement et longtemps, ou bien cacher l’or dans une grotte — et il ne reste alors qu’une tombe, un trésor... et un morceau de papier.";
			link.l1 = "Comme ça, tout simplement ?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Pas tout à fait. Les cartes coûtent cher, et attirent d’autres chasseurs comme vous. Et parfois, le butin couvre à peine les ennuis. Même le grand Albert Blackwood n’a pas réussi du premier coup. Faites de la chasse au trésor un métier — et plus vous en trouverez, plus les récompenses seront grandes. Et avec une amulette de chance — ça deviendra encore plus amusant !";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+" ! Un instant, s’il vous plaît.";
			link.l1 = "Vous allez encore me faire la morale, monsieur Pinchon ? Je n’ai pas touché à votre précieuse encre !";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "Alors avec quoi vous écrivez en cachette dans votre petit carnet ? Avec de l’eau bénite ? Il n’y avait pas d’encre dans l’inventaire des passagers. Mais enfin, vous avez des ennuis plus sérieux.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "Et deux cents de plus pour le cabestan endommagé. Le câble de l’ancre a cédé.";
			dialog.text = "Je vous rappelle que vous devez encore trente pesos à la caisse du navire — pour le tonneau d’eau de pluie abîmé. Votre tentative comique de laver votre chemise aurait pu coûter bien plus cher si la pluie n’était pas revenue. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Il ne me manquait plus que des dettes à mon arrivée. Tenez.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Il ne me manquait plus que des dettes à mon arrivée. Tenez.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "C’est tout ? Ce n’est pas une dette de jeu, tout de même. Je suis occupé. Vous attendrez notre arrivée au port.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Dommage. Passons aux choses sérieuses — j’ai un travail pour vous.";
			link.l1 = "Vous n’êtes pas très sociable, n’est-ce pas ?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "Un instant, je vais compter.";
			link.l1 = "N’oubliez pas de recompter aussi les miettes de pain sur ma table après le dîner.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Félicitations. La trésorerie du navire n’a plus rien à vous reprocher. Pour l’instant.\nPassons aux choses sérieuses — j’ai un travail pour vous.";
			link.l1 = "Vous n’êtes pas très sociable, n’est-ce pas ?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Pas trop, non. Mais je suis bon en calculs.\nEt vous, monsieur "+pchar.lastname+", savez-vous compter ?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Comptable) Les livres de comptes et les lettres de change ne me sont pas étrangers. Et je connais même le concept du zéro.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Assez pour faire durer une maigre pension paternelle toute une saison.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "O-o-oh ! Dommage que vous ne me l’ayez pas dit plus tôt — ce voyage aurait pu être bien plus intéressant.";
			link.l1 = "Vous parliez d’un travail ?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Pour votre propre bien — j’espère que vous ne deviendrez jamais armateur. Vous mèneriez à la ruine non seulement vous-même, mais aussi tous ceux qui seraient à bord avec vous.";
			link.l1 = "Vous parliez d’un travail ?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Oui. Je ne sais pas si vous le savez, mais le trésorier et le médecin sont les deux plus hauts gradés après le capitaine.\n"
			+ "Partir en mer sans eux deux, c’est risquer de perdre de l’argent — et sans argent, un navire n’est qu’un très coûteux morceau de bois.\n"
			+ "Sans trésorier, même une petite chaloupe peut ruiner son capitaine. Et un seul combat sans médecin peut décimer l’équipage, lançant une procédure d’embauche et de formation longue et onéreuse.\n"
			+ "Heureusement pour nous, j’assume les deux fonctions. Cela me permet de gérer des affaires personnelles et de recourir à certains services de l’équipage.\n"
			+ "Naturellement, ces services sont généreusement rétribués — et c’est justement le bon moment pour en solliciter un.\n"
			+ "Je veux que vous preniez cette liste, ce coffre de doublons — et que vous distribuiez les soldes aux membres de l’équipage.\n"
			+ "Strictement selon la liste ! C’est pour cela que je vous ai demandé si vous saviez compter.";
			link.l1 = "Pourquoi ne le faites-vous pas vous-même ? Après tout, si les gens attendent leur paie — qu’ils viennent la chercher.";
			link.l1.go = "OfficerKaznachey_10";
		break;

		case "OfficerKaznachey_10":
			dialog.text = "J’ai trop à faire pour le moment. Le voyage se termine dans quelques jours, et très bientôt il y aura une file de cent personnes ici, réclamant leur salaire.";
			link.l1 = "Vous avez mentionné des doublons...";
			link.l1.go = "OfficerKaznachey_11";
		break;
		
		case "OfficerKaznachey_11":
			dialog.text = "Une pièce d’or espagnole. Monnaie forte et véritable symbole de richesse. Les services les plus rares, coûteux et précieux — uniquement en doublons.\n"
			+ "On les conserve dans de petits coffrets comme celui-ci, pour plus de commodité.";
			link.l1 = "Et qu’est-ce que j’y gagne ?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Comptable) 150 pesos, plus 5 doublons pour un quasi-collègue. Et aussi la possibilité d’échanger des pesos contre des doublons à un bon taux.";
			}
			else
			{
				dialog.text = "150 pesos, et la possibilité d’échanger des pesos contre des doublons. Ce n’est pas grand-chose, mais le travail est simple.";
			}
			link.l1 = "Très bien. Donnez-moi la liste et le coffre.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Je crains que ce travail ne soit pas fait pour moi. Adieu, monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;

		case "OfficerKaznachey_11_otkaz":
			dialog.text = "C’est votre droit. Dans ce cas, ne me dérangez pas dans mon travail, monsieur "+pchar.lastname+".";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;
		
		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Tenez. Mais par pitié — n’oubliez pas de sortir les doublons du coffre, suivez rigoureusement la liste, et ne vous avisez pas d’en garder plus qu’il ne faut. Je veux aussi récupérer ce coffre vide.\n"
				+ "Et ne vous blessez pas, monsieur. Pourquoi diable portez-vous autant de choses ? Je vous conseille de déposer une partie de vos affaires dans un autre coffre.";
			}
			else
			{
				dialog.text = "Tenez. Mais par pitié — n’oubliez pas de sortir les doublons du coffre, suivez rigoureusement la liste, et ne vous avisez pas d’en garder plus qu’il ne faut. Je veux aussi récupérer ce coffre vide.";
			}
			link.l1 = "Comme vous voulez. À bientôt, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait": // ждёт выполнения квеста
			dialog.text = "Alors, des nouvelles ? Vous avez distribué les soldes ? Tout est revenu ? Les doublons restants, le coffre vide ?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Tout est prêt.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Pas encore, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Voyons voir...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "On disait que vous saviez compter. Il en manque. Cela signifie que ma comptabilité vient de se compliquer, et vous m’avez causé un problème au lieu d’en résoudre un.\n"
				+ "Par conséquent, monsieur "+pchar.lastname+", vous ne recevrez pas de paiement.";
				link.l1 = "Mais vous me changerez quand même les doublons ?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "On disait que vous saviez compter. Il y en a trop. Cela signifie que ma comptabilité vient de se compliquer, et vous m’avez causé un problème au lieu d’en résoudre un.\n"
				+ "Par conséquent, monsieur "+pchar.lastname+", vous ne recevrez pas de paiement.";
				link.l1 = "Et pour l’échange ?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Parfait. Heureux de voir qu’un jeune sait manier les chiffres. Merci, monsieur "+pchar.lastname+". Voici votre paie — et une petite prime, presque collègue.";
					link.l1 = "Et pour l’échange ?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Parfait. Heureux de voir qu’un jeune prend l’argent au sérieux. Merci, monsieur "+pchar.lastname+". Voici votre paie.";
					link.l1 = "Vous échangez toujours les doublons ?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Pourquoi pas. Cent quinze pesos pour un doublon. N’hésitez pas à revenir si cela vous intéresse.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Bien sûr. Cent cinq pesos pour un doublon. N’hésitez pas à revenir si cela vous intéresse.\n"
			+ "Et permettez-moi un conseil : si, par malheur, le destin vous met aux commandes d’un navire — engagez un trésorier en priorité. Même un mauvais vous fera économiser une fortune.";
			link.l1 = "Merci, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Évidemment ! Cent pesos pour un doublon — un taux honnête. Les banques des Caraïbes vous prendraient bien plus.\n"
			+ "Et permettez-moi un conseil : si, par malheur, le destin vous met aux commandes d’un navire — engagez un trésorier en priorité. Même un mauvais vous fera économiser une fortune.";
			link.l1 = "Merci, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;

		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Vous flânez, monsieur "+pchar.lastname+" ?";
			link.l1 = "Vous aussi, relégué à la cale ?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Je suis le médecin de bord, "+pchar.lastname+" ! Bientôt, la salle commune sera remplie de blessés, et je verrai plus de sang que n’importe quel combattant. Et même si je n’étais que le trésorier — je me battrai comme tout le monde. Non, le seul à s’être vu relégué dans la cale confortable — c’est vous.";
			link.l1 = "Alors qu’est-ce que vous faites ici ?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;

		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "La bataille ne commencera que dans quelques heures, c'est donc le moment parfait pour clôturer les comptes quotidiens. Vous avez mon coffre de doublons, de Maure. Veuillez le rendre.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Prenez-le. Et ne montrez plus votre tête ici en bas.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "J'ai laissé vos affaires ailleurs.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "Je n'en avais pas l'intention. Je ne suis pas un rat de terre - ma place n'est pas dans la cale. Adieu.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Ailleurs... Nous en discuterons après la bataille - en présence du capitaine. À bientôt.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;

		case "TreasurerTrade":
			dialog.text = "Les doublons vous intéressent, monsieur "+pchar.lastname+" ?";
			link.l1 = "Marchandons un peu.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Pas pour l’instant.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;

		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Cap’taine, alerte ! Des pirates à l’horizon !";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, veuillez escorter poliment monsieur "+pchar.lastname+" à la cale. Et vérifiez que monsieur Drussac daigne se réveiller et prépare les servants d’artillerie au combat.";
			link.l1 = "Capitaine, je suis prêt à me battre ! Un noble ne peut...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Si je peux être utile...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Quoi ? On n’aura même pas le bourgogne ?";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, débarrassez-moi de lui. Au travail, feignants ! Hisser les voiles !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, débarrassez-moi de lui. Au travail, feignants ! Hisser les voiles !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, débarrassez-moi de lui. Au travail, feignants ! Hisser les voiles !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Nom d’un chien ! Voilà des teignes obstinées !";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			PlaySound("VOICE\\Russian\\OliverTrast01.wav");
			//PlaySound("VOICE\\Spanish\\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\\abordage.wav");
			PlaySound("interface\\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "Et toi, qu’est-ce que tu fiches là ?! Tu as abandonné les tiens pour te planquer, sale rat de cale ?! Je vais te vider les tripes, moi !";
			link.l1 = "Tu aurais mieux fait de ne pas venir dans ma cale. C’est moi qui vais te vider les tripes.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Tu tiens à peine debout, et la plupart du sang sur toi n’est même pas le tien.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duelliste) Ça m’avait manqué.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Héhé. Vas-y, petit freluquet.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Héhé. Alors je n’ai rien à perdre.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "Tu délires ou quoi ?!";
			link.l1 = "Deux mois. Deux mois que je n’ai pas pu tirer l’épée. En garde !";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Au moins vous êtes vivant... Moi, c’est fini. Je suis fichu. Ils m’ont bien assommé à coup de gouvernail...";
			link.l1 = "Que s’est-il passé ?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Un abordage ! Aargh ! Sacrés teigneux !\nÉcoutez bien : on a tenu le pont-batterie, mais en haut, la fête ne fait que commencer. Je vous jure qu’ils vont revenir. Prenez ce tromblon ! Nom de Dieu, attention ! Il est chargé !";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Tireur d'élite) Inutile de t’inquiéter pour moi. Celui qui osera s’approcher sera criblé de trous.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Il y a de la mitraille. Si vous visez bien, vous pouvez descendre deux ou trois types d’un coup\nJ’ai confiance en vous, "+pchar.name+". Une fois qu’ils seront repoussés, fouillez les cadavres. Avec un peu de chance, vous trouverez de quoi me requinquer... sinon, je ne vous serai d’aucune aide.";
			link.l1 = "Tiens bon, Alonso. Voilà les invités !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Bien... Beau travail, "+pchar.name+". Vous avez trouvé quelque chose pour moi ?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Je crois que c’est ça. Même si ça a une drôle de tête.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Je cherche encore !";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;
		
		case "SailorAlive_12":
			dialog.text = "Et le goût n’est pas mauvais, ha ha ! Merci, "+pchar.name+". Et vous avez abattu ces trois-là avec classe. Puisque vous êtes vraiment un noble gentilhomme, alors prenez le commandement. À deux, on tiendra le pont — et si les gars en haut s’en sortent aussi, cette journée sera à nous !";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Là, c’est mieux. Le tromblon est chargé ?";
				link.l1 = "Je m’en occupe... Mais pourquoi ce silence soudain ?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Puisque vous êtes vraiment un noble gentilhomme, alors prenez le commandement.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Là, c’est mieux. Le tromblon est chargé ?";
			link.l1 = "Je m’en occupe... Mais pourquoi ce silence soudain ?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Pour ajouter un peu de dramaturgie. Ça va commencer.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "On termine là où tout a commencé. Merci de m’avoir sauvé la peau, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Je crois qu’on est quittes. Je ne me souviens même plus comment tu m’as sorti de là.";
			}
			else
			{
				link.l1 = "Je crois qu’on est quittes. Sans toi et les gars, j’y serais resté.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Vous auriez pu rester caché dans la cale, comme on vous l’avait dit. Dommage que le capitaine ne soit plus là pour vous passer un savon.";
			link.l1 = "Il a fallu l’extraire de sous une montagne de cadavres. Combien d’enfoirés a-t-il eu le temps de descendre ?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Certains disent qu’il en a tué trois. D’autres — au moins une douzaine. Je crois que seul le diable connaît le vrai chiffre.";
			link.l1 = "Tu ne m’as toujours pas expliqué ce qui s’est vraiment passé.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "Qu’est-ce que je pourrais dire ? Même nos canons de seize livres n’ont pas suffi contre une seule goélette pirate. Voilà ce que c’est qu’un navire taillé pour le vrai combat.\n"+
			"Il a foncé sur nous, et pendant qu’on manœuvrait, il nous a arrosés de mitraille et est passé à l’abordage. Vous auriez dû voir le carnage sur le pont — il n’y avait plus rien à faire pour le médecin.\n"+
			"Le pire, quand on se bat contre des pirates — c’est qu’il n’y a rien à gagner. Que des loqueteux. On n’a même pas pu récupérer leur navire.";
			link.l1 = "Et maintenant ?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;
		
		case "AfterBattle_Alonso_5":
			dialog.text = "Le navire tient la mer, et il reste assez d’hommes pour vous mener à Saint-Pierre comme prévu. Là, je chercherai un nouveau capitaine, et vous retrouverez votre frère pour lui raconter vos aventures. Et ensuite ? Seul Dieu le sait.\n"+
			"Mais une chose est sûre — vous avez votre place parmi nous. Pas mal pour un terrien, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Oh là là ! Vous allez tourner de l’œil. Ne vous inquiétez pas. C’est juste la peur qui sort de vous. Bienvenue aux Caraïbes !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}