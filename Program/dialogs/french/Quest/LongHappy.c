// диалоги персонажей по квесту Долго и счастливо
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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, quelle chance ! Je vous cherche depuis des mois !";
			link.l1 = "Ma chère, je n'achète pas de fausses cartes, d'informations douteuses et de rhum artisanal - merci ! Ou bien êtes-vous un chasseur de primes ? Et combien vaut ma tête maintenant ?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, monsieur, je... Je ne commerce pas de pacotille et ne tue pas de gens - ne touchez pas l'épée, vous n'en aurez pas besoin, je ne veux aucun mal ! Tout est bien plus prosaïque - je suis capitaine d'un navire de courrier. Je distribue le courrier. Et pour vous, j'ai une correspondance importante !";
			link.l1 = "Une lettre ? Qui est l'expéditeur, puis-je demander ?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Un abbé me l'a remis et m'a demandé de le livrer au capitaine de Maure en personne, de main en main. J'avais déjà perdu tout espoir de vous trouver et je voulais le laisser au bureau du port de Saint-Pierre, mais quelle chance - vous voilà!";
			link.l1 = "Oui, me voilà, j'attends - donne-moi la lettre.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Il y a un problème... L'abbé a dit que la livraison serait payée par le destinataire. Donc vous devez neuf mille deux cents pesos.";
			link.l1 = "Pour une telle somme, cela aurait dû m'être apporté en haute mer directement dans la cabine, accompagné de mon café du matin ! Tu peux garder la lettre pour toi.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "Et pourquoi je n'ai pas fait de la livraison de courrier ?! C'est plus rentable que la piraterie ! Voici ton argent en argent, ma chère, donne l'enveloppe.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Enchanté de traiter avec vous ! L'abbé Benoit vous envoie ses meilleurs voeux ! Adieu monsieur de Maure !";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Comme vous le souhaitez. Je laisserai l'enveloppe au bureau du port. Mais cela affectera le prix, je vous préviens. Et oui - l'abbé Benoit vous envoie ses meilleurs voeux.";
			link.l1 = "La lettre de l'Abbé Benoit ? Pourquoi ne l'as-tu pas dit dès le début ! Cela doit être important !";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "Alors, prenez-le depuis la tête du port. N'oubliez pas de prendre un prêt à l'avance. Adieu, capitaine de Maure.";
			link.l1 = "J'ai connu des pirates plus sincères que toi. Bonne chance, ma chère.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Pere Saint, vous etes plus tot que d'habitude aujourd'hui. Je vous en prie, votre escorte vous attend. Et vous, senor de Maure - le pere Vincento a appris que vous etiez en ville et vous presse de le rejoindre pour un diner.";
			link.l1 = "Je crains que l'Inquisiteur ne dîne seul. J'espère que cela ne lui coupera pas l'appétit. Et l'Abbé Benoit le privera également de sa compagnie. Vous savez qui je suis, alors je vous recommande. laissez-nous passer sans conflit et transmettez mes meilleurs vœux au Père Palotti.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Oui, j'ai beaucoup entendu parler de vous, et j'ai des instructions claires pour ne pas transformer la ville en bain de sang si vous êtes obstiné. Vous pouvez passer. Mais le père Vincento sera... mécontent. Gardez cela à l'esprit.";
				link.l1 = "Vous avez agi raisonnablement, monsieur. Je survivrai, d'une manière ou d'une autre, à la douleur dans mon cœur causée par l'insatisfaction du père-inquisiteur. Passez une bonne soirée !";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Oui, j'ai entendu parler de vous... beaucoup de choses intéressantes. Cependant, refuser de telles invitations est dangereux pour la santé, senor. Tout comme enlever les invités du père Vincento. Attrapez-les !";
				link.l1 = "Chacun a fait son choix. Je suis désolé qu'on en soit arrivé là. Aux armes, caballero !";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, félicitations ! Tu sais - je t'ai toujours apprécié, et Helen pour moi est comme une fille, donc je suis heureux pour vous deux. Sacrebleu... verser une larme dans une église, c'est tout ce que j'ai jamais voulu, suis-je en train de vieillir ou quoi ?";
			link.l1 = "Tout va bien, Jan, j'ai failli pleurer près de l'autel. De l'encens, peut-être ?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "D'accord, camphre, bon sang. Je me demandais pourquoi mes yeux piquent et mon nez gratte ! Très bien, nous discuterons à Sharptown, embrasserons Gladys et irons voir les autres. Ils ont des têtes comme si on signait la paix de Westphalie.";
			link.l1 = "Merci d'être venu ici, Jan. Je suis heureux de te voir, et cela signifie beaucoup pour Helen.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Te voilà enfin, Charles ! Ma corvette t'a devancé de presque un jour - une belle occasion de fierté.";
			link.l1 = "De rien Jan, mais où est Gladys, et ta femme ?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "J'ai renvoyé Gladys à Blueveld sur un navire marchand - elle n'approuve pas toutes ces fêtes flamboyantes. Joanna n'a pas pu venir - oh, je n'ai pas eu le temps de te le dire à la Martinique ! Imagine-toi - à mon grand âge, je vais devenir père légitime, qu'en dis-tu ? Écoute, si tu te dépêches, nos rejetons auront presque le même âge, hahaha !";
			link.l1 = "Jan, mes félicitations, ce sont de bonnes nouvelles!!! Nous devrions trinquer à cela!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Assurément ! Mais d'abord, à vous et votre moitié ! Hé, vous là-bas, fermez-la !!! Le vieux Diable de la Forêt doit faire un discours !\nKhe-khe... Alors, nos chers Monsieur et Madame de Maure... Merde ! Je ne peux pas parler comme ça ! Charles, Helen - vous deux, pour moi, êtes comme mes propres enfants, et je sais que dans cette salle, il n'y a personne qui ne serait pas heureux pour votre union ! Alors buvons, mes Frères, pour le bonheur de nos fidèles amis, pour le vent favorable dans leurs voiles et pour l'amour de Dame Fortune, aussi fort que leurs sentiments l'un pour l'autre !!! À la vôtre !";
			link.l1 = "Santé ! Merci Jan... oh, ce rhum est bien plus fort que d'habitude... Qu'est-ce que Nathan y a mélangé ?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Je n'en ai aucune idée, mais cela semble tout à fait juste. Vieux Faucon est généralement un expert en boissons. Allez, va rejoindre les autres, je dois préparer des boissons pour une bonne centaine d'âmes avides de se remplir la panse.";
			link.l1 = "Le Diable de la Forêt servant des boissons - quel spectacle ! Merci d'avoir pris l'organisation de la fête en main. Je reviendrai certainement, dès que j'aurai fait le tour de tout le monde - peut-être que quelqu'un a besoin d'aide.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Tout va bien, Charles ?";
			link.l1 = "Parfait, Jan !";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Et te voilà, enfin ! Comment ça s'est passé à la Martinique ? Sens-tu que ta vie a changé à jamais ?";
			link.l1 = "Cela a changé beaucoup plus tôt, Jan. Mais tout s'est étonnamment bien passé. Où est Joahnna et...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen ? La fille a levé l'ancre dès qu'elle a découvert ce que nous faisions, et a navigué vers l'horizon. Elle t'a transmis toutes sortes de chaleureuses félicitations, mais tout de même... tu lui as brisé le coeur, oh tu l'as vraiment fait. Cependant, tout ira bien, ce n'est que la jeunesse.";
			link.l1 = "Eh bien, le coeur veut ce qu'il veut, tu comprends ça.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Je le fais. Eh bien, Joahnna n'a pas pu arriver, imaginez - à mon âge avancé, je vais devenir un père légitime, qu'en dites-vous ? Écoutez, si vous vous dépêchez, nos rejetons auront presque le même âge, hahaha !";
			link.l1 = "Jan, mes félicitations, voilà une bonne nouvelle !!! Il faut trinquer à ça !";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Certainement ! Mais d'abord, à toi et ta meilleure moitié ! Hé, toi là-bas, ferme-la !!! Le vieux Diable de la Forêt doit prononcer un discours !\nCharles et Mary, toute la Fraternité lève ses gobelets en votre honneur maintenant ! Le bonheur des vrais amis réjouit l'âme de tout loup de mer, presque autant que la splendeur de l'or espagnol, ha-ha ! Bonne navigation, et que les vents favorables vous accompagnent dans votre voyage familial !!! À votre santé !";
			link.l1 = "Cul sec ! Merci Jan... oh, ce rhum est bien plus fort que d'habitude... Qu'est-ce que Nathan a bien pu y mettre ?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Je n'ai aucune idée, mais cela semble juste. Le vieux Faucon est généralement un expert en boissons. Allez, va rejoindre les autres, je dois préparer des breuvages pour une bonne centaine d'âmes avides de se rassasier.";
			link.l1 = "Cette taverne a vraiment besoin d'être renommée - 'Le Diable de la Forêt lui-même se tenait ici derrière le comptoir' ! Merci, Jan, je reviendrai certainement, dès que j'aurai fait le tour de tout le monde - peut-être que quelqu'un a besoin d'aide.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Comment vas-tu, Charles? Comment va le mariage?";
			link.l1 = "Très réconfortant, Jan. Je suis content que nous ayons réussi à nous rassembler ici. On dirait que les barils de rhum de Hawk commencent à montrer leur fond, n'est-ce pas ?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Oui, ils le sont ! Alors, il est temps d'ouvrir ce que tu as apporté ici. Et une autre chose - ces gars qui m'ont aidé au début se sont complètement saoulés dans la salle du fond. Tu sembles encore tenir debout, marié - peux-tu apporter une caisse d'un autre sherry ?";
			link.l1 = "D'accord, dites-moi juste où aller. Peut-être que je trouverai quelques têtes sobres en chemin pour m'aider. Bien que, la plupart de mes gars soient probablement déjà saouls comme des cochons.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "Le vin était entassé dans les caves sous le chantier naval, tu te souviens ? Hawk a dit de le garder dans le couloir du fond, ''pour l’économiser jusqu’aux fêtes'' - qu'il dit. Il dit aussi que la température et l'humidité y sont parfaites, il dit que ce serait un endroit idéal pour une cave à vin. Eh bien, c'est un grand snob.";
			link.l1 = "Il a pris la bonne décision, Jan. J'irai, mais d'abord, dis-moi - as-tu vu ma femme ?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Elle et Dannie sont allées quelque part. Laisse les filles discuter, Charles, et nous devons commencer une vraie fête. Va dans les caves pendant que je m'occupe de la nourriture. Car ça sent que bientôt nous mangerons du charbon au lieu de côtelettes de mouton !";
			link.l1 = "D'accord, va sauver la viande, je vais apporter notre vin.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, que s'est-il passé, avez-vous déclenché une bagarre de soûlographes ?!";
			link.l1 = "Non, Jan, nous avons combattu ensemble contre des coupe-jarrets armés dans les cachots. Nous nous en sommes occupés, mais ils n'étaient que des éclaireurs - l'escouade principale est juste derrière nous !";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Une escouade ? De quoi parles-tu ?! Marcus, viens ici ! Charles, allez, raconte-nous tout.";
			link.l1 = "Comme je l'ai dit : il y a des salopards dans les cachots sous le chantier naval. Bien armés. Nathan et moi les avons combattus et avons miraculeusement mis tout le monde à terre. Mais il y en a d'autres en route - j'ai entendu dire que l'un d'eux a été envoyé chercher de l'aide. Et oui, l'un d'eux se souvenait d'un certain Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Je reconnais leurs visages... celui-ci, et ce salaud étendu près de la porte. Ce sont des brutes de Jacques le Gentilhomme. Je ne me souviens pas de leurs noms, mais j'en suis sûr.";
			link.l1 = "Alors c'est la faute de Barbazon ? Est-il devenu fou ou quoi ?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Je ne sais pas, mais il semble que le Kindman ait décidé de profiter de l'occasion pour organiser un remaniement radical parmi les barons de la Confrérie.";
			link.l1 = "Dans ce cas, j'espère qu'il se montrera lui-même - ça fait longtemps que je rêve de lui faire quelques trous dans le corps. Salaud, il a ruiné mon mariage, pensez-y ! En avant, dans les rues ! Nous allons préparer un accueil digne de ce nom pour nos invités !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "Et voici notre héros fatigué ! Ha, Charles, c'était quelque chose ! Jacques, un tel rat ! Regarde comment il a tout arrangé - il a presque réussi !";
			link.l1 = "Oui, probablement, nous aurions dû tuer ce salaud lorsque nous en avions terminé avec Jackman. Cependant, c'est fini. Barbazon est mort.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Eh bien, je ne peux pas dire que tout soit terminé - notre vie continue ! Bien que je me sente complètement épuisé. Je suis trop vieux pour sauter à la mer depuis une coque couverte de feu et nager une heure entière jusqu'au rivage, en surveillant les requins. J'espère que nous avons encore un peu de rhum...";
			else dialog.text = "Eh bien, on ne peut pas dire que c'est fini - notre vie continue ! Nom de Dieu, je me sens dix ans plus jeune ! Cela fait longtemps que je n'ai pas combattu comme ça ! J'espère que tes stocks de rhum et de vin n'ont pas été volés pendant la pagaille - il faut bien trinquer à ça !";
			link.l1 = "Oui, je boirais aussi, mais d'abord je dois vérifier la résidence, je ne sais pas si on vous l'a dit ou non...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "C'est à propos de votre compagnon indien ? Oui, j'ai entendu, comment cela est-il arrivé ?";
				link.l1 = "Il a sauté pour couvrir ma femme et Dannielle d'une balle tirée par un salaud. Nous devrions partir, je te raconterai en chemin.";
			}
			else
			{
				dialog.text = "C'est à propos de Nathan ? Oui, j'ai entendu, mais je n'ai pas compris comment cela s'est passé ?";
				link.l1 = "Il a sauté pour couvrir nos femmes d'une balle tirée par un salaud. Nous devrions partir, je te raconterai en chemin.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Reste fort, Charles. Je suis vraiment désolé pour tes gars. Aujourd'hui, beaucoup de braves types sont partis, et pour chacun d'eux, en enfer, Barbazon mettra plus d'huile dans sa chaudière.";
				link.l1 = "Ça n'a pas de sens... bon sang ! C'est dur, Jan... J'ai déjà perdu des amis, mais je ne peux pas m'y habituer. Je ne sais pas si je peux continuer.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Alors, ce type tranquille, le médecin ? Je suis désolé, Charles, sincèrement. C'était un bon gars.";
					link.l1 = "Oui, Jan, moi aussi. Mais, j'ai peur que le monde de la science ait perdu bien plus que moi. C'était un génie... raffiné, comme tous ceux-là, mais... putain...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Eh bien, il semble que ce soit fini. Aujourd'hui, beaucoup de braves gars sont partis, et pour chacun d'eux, en enfer, Barbazon obtiendra plus d'huile dans sa chaudière, mais "+sTemp+" sera bien et c'est le principal.";
					link.l1 = "Tu as raison, Jan, et cela m'enlève un grand poids de l'esprit. Comment vont les autres barons ? Sont-ils bien portants ?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "Le dernier déchet de Jacques Barbazon. Tu as raison, si nous l'avions tué avant, tout aurait pu être autrement.";
			link.l1 = "Mais à quoi bon regretter le passé ? Le passé ne peut être changé. Comment vont les autres barons ? Est-ce que tout le monde a survécu ?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Aucun homme ne peut s'y habituer.  Trinquons pour nos gars ? J'ai trouvé une bouteille sur la table, elle a miraculeusement survécu à ce bazar.";
			link.l1 = "Verse, je... Diable... mille damnations !";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Raconte-moi à leur sujet. Ce médecin semblait intelligent. Il s'exprimait si sagement.";
			link.l1 = "Il l'a fait. Mais, je crains que le monde de la science ait perdu bien plus que moi. C'était un génie... sophistiqué, comme tous les autres. Le maître des miracles !";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "À propos de l'Indien ? Où l'avez-vous trouvé ?";
			link.l1 = "Je l'ai sauvé de la prison en Guadeloupe, presque immédiatement après mon arrivée. Une histoire vraiment drôle et stupide. Donc, il est resté avec moi. Il l'a choisi, je lui ai donné la liberté mais il est resté à mes côtés - je l'ai sauvé et il pensait qu'il me devait jusqu'à la fin de sa vie. Laconique, habillé étrangement, mais plus fidèle que n'importe quel chevalier, il avait aussi un talent, il pouvait toucher une pièce avec un mousquet en plein vol à n'importe quelle distance.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Eh bien, il t'a payé la dette, que puis-je dire. Sauvé "+sld.name+" et Dannielle de ce salaud. Il me semble que c'est une fin digne pour un tel brave guerrier.";
			link.l1 = "C'est bien, Jan. Buvons à la mémoire des défunts... Qu'ils trouvent la paix. Comment vont les autres barons ? Vont-ils bien ?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Cette nuit nous a coûté cher. Je ne sais même pas quand les Frères se remettront de ce massacre. Kindman a parfaitement choisi le moment et le lieu pour frapper. Il a presque réussi - encore un peu et tout serait terminé. Mais nous avons perdu beaucoup moins que nous aurions pu.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "Le Requin est à l'infirmerie, son navire a reçu une volée de vingt-quatre livres. Il a été projeté par-dessus bord, s'est cassé quelques côtes, a avalé de l'eau de mer, mais il vit, dans quelques jours il sera comme neuf.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard n'a eu que quelques égratignures - il défendait le rivage et nettoyait les catacombes. Maintenant, il est dans le port, organisant des hôpitaux pour les blessés et des funérailles pour ceux qui n'ont pas eu de chance.";
			else dialog.text = "Bernard n'a pas eu de chance, il nettoyait les maisons après l'attaque depuis les catacombes et il est tombé sur une bande de ces salauds dans les entrepôts. Il a pris une balle, en pleine tête. C'est dommage, c'était un bon capitaine... Tyrex sera furieux quand il l'apprendra.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard n'a eu que quelques égratignures - il défendait le rivage et nettoyait les catacombes. Maintenant, il est dans le port, organisant des hôpitaux pour les blessés et des funérailles pour ceux qui n'ont pas eu de chance.";
			else dialog.text = "Bernard n'a pas eu de chance, il nettoyait les maisons après l'attaque des catacombes et est tombé sur une bande de ces salauds dans les entrepôts. Il a pris une balle, droit dans la tête. C'est dommage, c'était un bon capitaine... Tyrex sera furieux quand il l'apprendra.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Pour ce qui est de Hawk, tu sais. Dannie ne le laissera pas quitter l'île avant au moins un mois, c'est certain. Il avait une affaire en tête... oh, eh bien.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus va bien comme toujours. Dès qu'il a mis pied à terre, il s'est immédiatement mis à secouer les âmes des sentinelles qui ont négligé toute cette crasse. Il parvient encore à commander la restauration de l'ordre dans la ville. Un homme de fer, sans aucun doute.";
				link.l1 = "Le fer est plus doux. Je suppose que notre baron est fait d'un métal encore inconnu de la science, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Seulement avec Marcus, c'est incompréhensible, son navire a été abordé, mais les survivants prétendent qu'il a réussi à sauter par-dessus bord. J'ai déjà envoyé les chaloupes pour fouiller la baie. J'espère qu'il s'avérera que notre baron est assez coriace pour ne pas abandonner si facilement.";
				link.l1 = "C'est mauvais, mais il est trop tôt pour pleurer sur lui, Marcus ne nous abandonnerait pas aussi facilement. Attendons le résultat des recherches.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus a nagé jusqu'à la rive après que son navire ait été coulé. Eh bien, tu sais, Tyrex n'est pas de ceux qui se noieront pour une telle bagatelle. Maintenant, il est quelque part en ville. Probablement en train de secouer les âmes des sentinelles qui ont négligé toute cette saleté. Un homme de fer, sans aucun doute.";
				link.l1 = "Le fer coulerait. Je suppose que notre baron est fait d'un matériau encore inconnu de la science, haha !";
			}
			else
			{
				dialog.text = "Marcus va bien comme toujours. Dès qu'il a mis pied à terre, il a immédiatement commencé à secouer l'âme des sentinelles qui surveillaient toute cette crasse. Il parvient encore à commander la restauration de l'ordre dans la ville. Un homme de fer, sans aucun doute.";
				link.l1 = "Le fer est plus tendre. Je suppose que notre baron est fait d'un métal encore inconnu de la science, haha !";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "C'est tout. Eh bien, cela aurait pu être pire. Même ton mariage, Charles, s'est terminé... en bataille. L'important est que vous soyez tous deux en vie. Un petit conseil, en général... aimez... et n'osez jamais renoncer à vous battre pour cela !";
			link.l1 = "Merci Jan. Merci à vous tous... Je dois admettre, j'ai oublié que nous avions commencé par une célébration.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Alors, voici un rappel.";
			link.l1 = "Ouais, c'était une... fête sauvage.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Oh oui, c'était bien ça, attendez une minute. Il y a quelque chose - il me semble que vous aviez un Indien avec vous, n'est-ce pas, toujours à vos côtés ou regardant autour de vous comme si quelqu'un vous visait. Habillé de façon drôle, et très remarqué dans les grandes foules.";
			link.l1 = "Oui, Tichingitu, il a disparu au tout début de ce bazar, je commence à m'inquiéter pour être honnête. Sais-tu quelque chose ?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "On dirait bien. Notre barman faisait du bruit que sa nièce avait été enlevée, apparemment avant l'attaque. Il dit qu'ils l'ont vue avec une sorte d'Indien, il la portait sur son épaule le long du rivage à l'est de la ville. Je n'ai pas remarqué parmi les raclures de Kindman aucun Indien, mais je me suis souvenu du tien quand je l'ai entendu, alors je n'ai rien dit. Tu devrais y aller, le chercher ou quelque chose, avant qu'il ne s'attire des ennuis. Parce que le barman menace de le tuer s'il le trouve en premier. C'est un bon gars, mais pour sa nièce, il dévisserait n'importe quelle tête.";
			link.l1 = "Oui je connais le genre ne t'inquiète pas, et merci Jan, je vais aller le chercher tout de suite.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Eh bien, en général, quelque chose comme ça... Désolé, je suis nul en discours. Et maintenant, c'est encore pire - cette nuit nous a tous épuisés. Nous devrions tous nous reposer au moins une journée - ensuite nous déciderons comment procéder.";
			link.l1 = "Tu as raison, Jan. Je devrais y aller, j'ai besoin de me rafraîchir l'esprit.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Tu as bonne mine, Charles. As-tu bien dormi ?";
			link.l1 = "Oui, on nous a donné une maison douillette à la périphérie de la ville. J'ai même pensé que j'avais rêvé de toute la folie qui s'est passée hier. Et te voilà Jan, tu as une sale tête. Qu'est-ce qui s'est encore passé ?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Ah non, ce n'est rien, je n'ai juste pas encore dormi. Vous savez... ranger la ville après tout ce qui s'est passé ici est une tâche ardue.";
			link.l1 = "Comment vont Dannie et Nathan ? Où est tout le monde ?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Se reposent. Ne les dérangez pas, Dannie a prévenu tout le monde qu'elle a pris des fusils au lit aujourd'hui... Dodson est en mer, parti chercher d'autres navires pour sécuriser l'île afin que cela ne se reproduise plus, d'autres enterrent les défunts au nord de l'île.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus n'a pas encore été trouvé, mais nous pouvons gérer cela, ne t'inquiète pas. Tu as fait tant pour nous tous, alors ne t'en fais pas. Tyrax reviendra tôt ou tard - nous le trouverons.";
			else dialog.text = "Marcus a terminé ici et s'est précipité sur le lougre de quelqu'un vers Hispaniola. Il est nécessaire de résoudre quelques problèmes survenus après la mort de Barbazon. Il vous a envoyé ses salutations et ses meilleurs voeux à vous et à votre femme.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Eh bien, les Frères ont résisté à ce coup. Bientôt, nous nous lèverons plus forts que jamais. Kindman et Jackman ont ébranlé notre unité trop longtemps, maintenant qu'ils sont partis et mon cœur sent - nous ferons trembler les Caraïbes plus d'une fois. L'Âge d'Or arrive pour ceux à qui les lois et les rois ne plaisent pas, souvenez-vous de mes paroles.";
			link.l1 = "Ce serait agréable. Je ne suis pas sûr de pouvoir supporter l'Ancien Monde désormais. Je n'aurais jamais cru en venant ici que je tomberais amoureux de la liberté de la mer, de ces couleurs folles des couchers et levers de soleil, que je trouverais la meilleure femme au monde et... des amis à qui je confierais ma vie.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Eh bien, vous connaissez la route, décidez-vous. Chez nous, vous êtes toujours le bienvenu.";
			link.l1 = "Merci, Jan. Cela signifie beaucoup pour moi.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "Mais d'abord, il reste quelque chose d'important. Charles, pendant que tu dormais, nous nous sommes réunis et nous avons décidé\nPuisque Barbazon est mort, les Frères ont besoin d'un nouveau baron. Comme il y avait une majorité claire parmi nous ici, et que la décision a été prise à l'unanimité, la voilà. Félicitations - tu es le nouveau Baron de Le François. Mais attends ... Je comprends - tu es une personne mondaine, et tu n'as pas le temps de mener les affaires dans cet endroit agréable, alors nous avons mis une personne de confiance là-bas, et tu fais ce que tu veux. Souviens-toi juste - ta voix compte parmi les Frères maintenant.";
			link.l1 = "Jan, je... je suis sans voix... C'est un grand honneur, je ne sais même pas...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Allez ! Vous avez parfaitement prouvé votre valeur avec Tyrex, et ensuite avec toute cette histoire de l'héritage de Sharp. Vous êtes la bénédiction de Dieu lui-même. Pour vous, rien ne changera - faites comme prévu, et en votre absence, votre homme prendra en charge toutes les affaires.\nIl y a un gars prometteur, Jan David, c'est un des Boucaniers. Un Français, un type honnête, avec un esprit brillant et il sait comment l'utiliser, comme vous. Mais il me faudra un peu de temps pour le trouver - il semble qu'il ait été capturé par les Espagnols, mais cela peut être résolu, ne vous inquiétez pas. Je veillerai à ce qu'il vous envoie votre part dès qu'il sera à l'aise avec les affaires.";
			link.l1 = "Je ne m'attendais vraiment pas à ce que tout soit ainsi. Eh bien, puisque tu as déjà décidé ainsi, qu'il en soit ainsi. Le Baron Pirate Charles de Maure !";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Vive le baron ! Si quelqu'un mérite ce nom, c'est bien vous. Portez-le avec fierté, et n'oubliez pas - vous êtes des nôtres désormais, peu importe la beauté de l'uniforme que vous portez, ici, juste en dessous, bat le cœur d'un véritable pirate.";
			link.l1 = "Je ne sais pas, peut-être que tu exagères... Mais je ferai tout ce que je peux pour justifier ta confiance.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Que vas-tu faire maintenant ? Retourner en Europe, revoir ton père, le présenter à ta femme ?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Oui, mais d'abord, je dois dire adieu à quelqu'un... Tu sais ce que je veux dire.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Peut-être pas si tôt. Encore une fois, je voguerai à travers l'archipel, je veux respirer cet air de Liberté pour la dernière fois.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Eh bien, vous avez un navire, vous pouvez rentrer chez vous quand bon vous semble.";
			link.l1 = "J'espère bien. Merci Jan, merci à vous tous et à plus tard, mon vieux ami ! Passe le bonjour aux Hawks et Shark !";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Oui, c'est difficile, mais nous devons le faire. Vers la mer ?";
			link.l1 = "Non, je vais naviguer vers Antigua. "+sTemp+" reposer en paix dans un endroit qui est devenu notre foyer, pour un temps.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Dis-lui quelques mots gentils de ma part aussi. Et ne t'inquiète pas - nous pouvons gérer cela seuls désormais. Tout ira bien.";
			link.l1 = "Merci Jan. A bientôt mon vieil ami ! Remets mon bonjour aux Faucons et au Requin !... Eh bien, ce sera Antigua.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Jeune homme, tu as grandi davantage à mes yeux aujourd'hui. Tu as fait tant pour Helen, que les mots de gratitude ne suffiront pas. J'espère seulement que tu prendras soin d'elle à l'avenir. Si son père était vivant et voyait cela, comme il aurait été heureux... oh je suis désolé.";
			link.l1 = "C'est bon, Gladys. Tu as traversé l'archipel pour soutenir Helen en ce jour. Nous apprécions vraiment ta visite avec Jan, merci.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, je m'excuse pour cette familiarité, mais je le dirai ainsi - Charles, mon ami, je suis sincèrement heureux pour vous ! Si je peux faire quelque chose pour vous ou votre fiancée, dites-le simplement !";
			link.l1 = "Je vous remercie, Baron, je suis si heureux, et les vignobles que mon père voulait comme dot, je pense pouvoir me racheter - heureusement, ma situation financière pendant mon séjour dans le Nouveau Monde s'est considérablement améliorée.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Oui, je suppose que tu peux t'offrir à peu près tout ce que tu veux, Charles. Excuse-moi, mais je vais faire ma contribution en tant que père représentatif - Aujourd'hui, je vais écrire à mon bon ami le Ministre des Finances. Ta choisie se verra accorder le titre de noblesse, et, je pense, nous lui trouverons quelque bon domaine, disons en Gascogne, parmi ceux qui ont été saisis pour dettes, et lui assigner rétroactivement. Ainsi, personne n'osera dire que le Chevalier de Monper a trouvé une épouse de basse condition !";
			link.l1 = "Je ne crois pas que je me soucie de tels commérages, mais merci, Baron. Cependant, tu ne devrais pas";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "J'en suis plus que satisfait ! Maintenant, va, Charles, accorde ton attention aux autres invités. Et encore une fois, accepte mes plus sincères félicitations !";
			link.l1 = "Moi et ma femme vous remercions. A bientôt, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, je m'excuse pour cette familiarité, mais je le dirai ainsi - Charles, mon ami, je suis sincèrement heureux pour toi ! Si je peux faire quelque chose pour toi ou ta fiancée, dis-le seulement !";
			link.l1 = "Merci, Baron, mais vous avez déjà fait beaucoup pour moi. Il nous suffit que vous ayez répondu à l'invitation.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Comment aurais-je pu ne pas répondre, Charles ! Mais écoute - je veux vous offrir, à toi et ta belle épouse, un cadeau digne, mais je ne peux rien trouver que tu ne puisses obtenir toi-même avec de l'argent ou une épée. Par conséquent, j'écrirai à mon ami le Ministre des Finances à Paris, et au moment où tu arriveras en Europe, tu seras attendu pour signer le rescrit royal de l'exaltation du nom de de Monper au titre de Barons de Monper ! Non, pas un mot, c'est le moins que je puisse faire pour toi.";
			link.l1 = "Je ne sais même pas quoi dire, Baron... Père sera si heureux. Je vous remercie sincèrement.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, je vous en prie, acceptez mes sincères félicitations ! Votre élue est tout simplement un miracle ! Je pense qu'aujourd'hui, la mode coloniale a reçu un fort ... coup vers une nouvelle direction. Votre originalité m'a toujours fasciné ! Puissiez-vous et votre belle moitié vivre heureux pour toujours !";
			link.l1 = "Merci, Baron. Vous nous avez honoré de votre visite.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Comment pourrais-je rester loin, mon ami ? Nous avons traversé tant de choses ensemble et je suis fier de t'appeler mon ami, Charles. Souviens-toi - mes portes te sont toujours ouvertes, quoi qu'il advienne.";
			link.l1 = "Comme les portes de la famille de Monper vous seront toujours ouvertes, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, mon ami, c'est un jour très important, et je suis heureux que tu m'aies invité à le partager avec toi. Toi et moi avons parcouru un long et difficile chemin, et devenir le père représentatif de mademoiselle... je te prie de me pardonner - Madame de Maure, c'est un honneur pour moi, crois-moi. De tout cœur, je te souhaite bonheur !\nEt s'il te plaît, fais-moi savoir quand tu comptes te rendre en Europe - moi, en tant que père représentatif de ta choisie, j'enverrai à ton père tous les cadeaux de mariage nécessaires. Crois-moi, personne ne dira que la fiancée du chevalier de Monper est pauvre ou indigne !";
			link.l1 = "Si je puis me permettre, Chevalier, à quelques lieues, au nord du domaine de Monper, il y a de bons vignobles, ils appartiennent à la famille La Brigne et je...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Pas un mot de plus, mon ami, pas un mot ! J'écrirai immédiatement à mon représentant autorisé à Lyon - à votre arrivée, ces vignobles seront remis à votre élu.";
			link.l1 = "Merci, Chevalier. Tu as raison - notre... amitie, a traverse... beaucoup. Mais, je suis vraiment content que tu aies partage cette journee avec nous. A bientot et merci encore !";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, mon ami, c'est un jour très important, et je suis heureux que tu m'aies invité à le partager avec toi. Nous avons parcouru un long et difficile chemin, et témoigner aujourd'hui à ton mariage est un honneur pour moi. De tout cœur, je te souhaite bonheur ! Et fais-moi savoir quand tu vas en Europe - j'enverrai à ton père des cadeaux de mariage dignes.";
			link.l1 = "Il n'y a pas besoin de cela, Chevalier. Merci d'avoir répondu à mon invitation.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Comme je l'ai dit - c'est un honneur pour moi ! Mais attendez, mon ami, j'aimerais vous présenter quelque chose à cette occasion - je suis sûr que cela plaira à la fois à vous et à votre élue. De belles pierres de nos mines en Nouvelle-Guinée - trouvez-leur un cadre convenable et madame de Maure brillera même lors de la réception royale ! Si vous la convainquez de porter une robe, bien sûr...";
			link.l1 = "Oh, vous ne devriez vraiment pas, chevalier. Merci encore.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, mon ami, permets-moi de te féliciter ! Nous avons parcouru un chemin long et difficile, et je suis sincèrement heureux d'être ici aujourd'hui. Notre Seigneur en est témoin - tu mérites ton bonheur ! Conserve-le et protège-le - je te souhaite de nombreuses années de bonheur à venir !";
			link.l1 = "Merci, Chevalier, ma femme et moi vous sommes très reconnaissants.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, quelle fête, et combien de gens importants ! Permettez-moi de vous souhaiter de tout cœur bonheur et bonne santé, et des enfants pour la joie ! Comme on dit - 'gor'ko' !";
			link.l1 = "Merci, Fadey, tu m'as honoré en acceptant de venir.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Mais, je ne comprends pas bien pourquoi il y a tant de monde comme si nous ne concluions pas un mariage, mais une grosse affaire commerciale, et toujours pas assez de bières et de vodka à mon goût ici... haha ! Eh bien, je plaisante, Charles, pourquoi es-tu devenu complètement pâle ? Donne-moi une accolade, capitaine marié !";
			link.l1 = "Ouah... Fadey, tu es fort comme un ours !";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Attends, Charles, ne t'en va pas - il n'est pas digne pour l'invité de venir au mariage sans cadeaux. Tiens, prends-les. Je sais - tu as essayé de trouver toutes ces lames, et certaines, tu les as évidemment aimées. Alors accepte-les - accroche-les dans une propriété familiale et souviens-toi de Fadey Moskovit d'un mot aimable!";
			link.l1 = "C'est un vrai cadeau ! Merci, Fadey. Ce sont vraiment des armes merveilleuses, et elles prendront leur place légitime dans le domaine de Monper, je te le promets !";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, quelle fete, et combien de personnes importantes ! Laisse-moi te souhaiter du fond du coeur bonheur et bonne sante, et des enfants pour la joie ! Comme on dit - 'gor'ko' ! Donne-moi une accolade, toi, capitaine marie !";
			link.l1 = "Ouah... Fadey, tu es fort comme un ours !";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, je ne pouvais pas manquer cela, je te félicite, toi et ton élue, de tout mon cœur ! Soyez heureux ! Tu sais, il y a quelques mois, j'ai marié ma fille à un bon homme et amoureux, mais honnêtement, j'étais déçu que ce ne soit pas toi... Eh bien, d'accord... mais qu'est-ce que je raconte - félicitations ! Puissiez-vous vivre heureux pour toujours !";
			link.l1 = "Merci, Prosper, je suis content que tu sois venu.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Félicitations, capitaine ! Un rite étrange, mais magnifique - Tichingitu l'a apprécié. Cependant, le capitaine devrait simplement enlever sa squaw et envoyer une rançon à ses proches.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Eh bien, d'une certaine manière, je l'ai fait, et ce n'est qu'une formalité. Merci, mon ami !";
			else link.l1 = "Eh bien, d'une certaine manière, je l'ai fait, et c'est juste une formalité. Merci, mon ami! Toi et moi parlerons plus à Sharptown - il y aura beaucoup moins d'officiel et plus de plaisir sincère, je te le promets!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "L'eau-de-vie encore ? Tichingitu ne saurait dire qu'il aime ça. Peut-être qu'une embarquement de fête fera mieux l'affaire, ou au moins danser autour d'un feu de camp ?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "J'espère bien que nous n'aurons pas à danser autour de feux de joie avant la fin, et je préfère éviter l'abordage. Très bien, sois patient - il ne reste plus grand-chose, et nous nous rendrons immédiatement à la taverne.";
			else link.l1 = "Je crains que nous ne dansions autour des feux de joie bien avant la fin, et je préférerais éviter l'abordage. Très bien, sois patient - il ne reste qu'un peu, et nous mettons immédiatement les voiles vers Sharptown.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitaine, félicitations encore une fois ! Tichingitu apprécie davantage cette célébration que la précédente. Le capitaine sait choisir ses amis - ici, il y a plus de sincérité, moins d'hypocrisie et de faux cheveux.";
			link.l1 = "Merci, mon ami ! Ne bois surtout pas l'eau-de-feu - elle est très forte ici.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Merci, mon ami ! Prenons un verre ? Je sais, tu n'aimes pas ça, mais aujourd'hui, tu devrais essayer !";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu n'aime pas l'eau-de-feu, mais si le capitaine insiste, aujourd'hui c'est possible de faire. A votre bonheur, et votre squaw !";
			link.l1 = "Et à toi, Tichingitu ! À ton amitié et ta loyauté !";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Belle fête, capitaine.";
			link.l1 = "Je suis heureux que vous soyez satisfait.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Capitaine, tu es sorti pour admirer les étoiles ? La nuit promet d'être très belle. Tichingitu aime la nuit sur la mer. C'est très paisible.";
			link.l1 = "Heureux de voir que tu tiens encore debout, mon ami ! Nathaniel et moi avons besoin de ton aide - les gars à la taverne sont à court de boissons, nous devons apporter quelques caisses de boissons du stock sous le chantier naval.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "En avant, capitaine. Tichingitu vous suit, comme toujours.";
			link.l1 = "D'accord, allons-y !";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Capitaine, il y a des gens, et ils sont armés, Tichingitu entend le cliquetis de leurs armes, et ils deviennent plus bruyants chaque seconde. Je n'aime pas ça. Cachons-nous.";
			link.l1 = "Allez, mate - ici c'est Sharptown, ici même aux latrines les gens vont armés de pistolets. Hé Nathan... eh bien, merde ! Voilà une bouteille de finie. Si ça continue comme ça, tu vas casser toutes les bouteilles ! Tiens-toi debout, sacrebleu ! Ha-Ha !";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Capitaine... vous... La tête de Tichingitu se fracasse comme un mât dans la tempête. Que s'est-il passé ?";
			link.l1 = "Je voulais te poser la même question ! Où étais-tu passé tout ce temps ?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu s'est réveillée il y a une heure à cause des cris de cette fille. Elle courait le long de la plage presque nue et hurlait quelque chose à propos des ravisseurs et des sauvages... Mais il n'y a personne ici à part nous. As-tu de l'eau ? Pas encore de l'eau-de-vie, Tichingitu la déteste maintenant ?";
			link.l1 = "Il y avait une flasque quelque part, si je ne l'ai pas perdue dans une bataille... la voilà. Comment as-tu réussi à faire ça ? Son oncle, un barman du coin, cherche un Indien qui a enlevé sa nièce, et menace de lui arracher sa tête vide emplumée. De qui penses-tu qu'il parle ?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu s'en souvenait. Elle aidait le Diable de la Forêt à la taverne avec le mariage. Nous avons bu de l'eau-de-feu avec toi, et Tichingitu en voulait plus. Et puis, cette squaw... elle était si mignonne et... Capitaine, je pense que je me suis souvenu ! Tichingitu voulait l'épouser... Il voulait construire un canoë et l'emmener loin... Esprits de miséricorde ! Des gens très mauvais sont arrivés avec de l'eau-de-feu. Peut-être les démons ou les mauvais esprits ! Tichingitu ne le fera plus jamais...";
			link.l1 = "Pour l'enlever ? Construire un canoë ?! Ahah, tu es un romantique, mon ami... Ha-ha... ha-ha-ha-ha-ha-ha oh, je n'en peux plus... je n'en peux plus de rire !";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Capitaine, Tichingitu a volé la squaw, oui... mais, pouvons-nous, eh bien... ne pas nous marier maintenant? Elle est... bruyante, comme un oiseau papagallo, et... pas si belle.";
			link.l1 = "Oui, mon ami, les femmes, s'amusant toute la nuit, sont un triste spectacle le matin. Ne t'inquiète pas, héros-amoureux, nous trouverons quelque chose. Allez, il faut retourner à Sharptown, tu as manqué ton embarquement de vacances...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Un abordage ? Le capitaine a mentionné une bataille auparavant. Les pensées n'obéissent toujours pas à Tichingitu. Que s'est-il passé en ville ?";
			link.l1 = "Une vraie bataille sur terre et en mer. Les canons tiraient toute la nuit, je suppose qu'on les entendait même à San Jose. Cependant, tu étais occupé avec une autre 'bataille', tout va bien je peux le comprendre... Allez, je te raconterai tout en chemin.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Merci, capitaine... Tichingitu ne le fera jamais...";
			link.l1 = "Ouais, 'l'étalon des plaines lointaines', tu ne devrais vraiment plus boire. Va te reposer. Je suis déjà épuisé aussi.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Capitaine, félicitations encore ! Tichingitu apprécie cette célébration plus que la précédente. Le capitaine sait choisir ses amis - ici il y a plus de sincérité, moins d'hypocrisie et de faux cheveux.";
			link.l1 = "Et beaucoup plus d'eau de feu. Au fait, boiras-tu un verre avec moi ? Je sais que tu n'aimes pas ça, mais nous avons une occasion inhabituelle !";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu n'aime pas l'eau de feu, mais si le capitaine insiste, aujourd'hui c'est possible. A votre bonheur, et à votre squaw! Puissiez-vous marcher sur le même chemin, et que le soleil et la lune y brillent toujours.";
			link.l1 = "Merci, mon ami. Santé à toi, Tichingitu ! À notre amitié !";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Grande ... célébration, je suis très heureux pour toi, Charles. Cependant, je ne te comprends toujours pas... Tenir une rose inestimable dans tes mains et l'échanger contre... une fleur des champs. Mais le coeur veut ce qu'il veut... Sois heureux mon ami. Puisse-tu vivre heureux pour toujours !";
				link.l1 = "Dans la fleur que tu tiens, la plus belle chose est ton sentiment envers elle. Sans cela, ce n'est qu'un amas de chair évanescente. Content que vous soyez venu, Votre Grâce.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Un jour magnifique, mon ami, et une occasion merveilleuse ! Accepte mes sincères félicitations ! Je me suis marié trois fois, et chaque fois j'ai tremblé comme la première, ah, jeunesse...";
				link.l1 = "Monsieur, vous êtes encore loin de la vieillesse, ne vous découragez pas. Merci d'être venu, Jacques !";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Attends, Charles. Tu m'as mal compris, je suis sincèrement heureux de tout mon cœur ! Et oui... tiens, prends-le. Notre... Ami commun, a vraiment insisté pour que tu le reçoives exactement aujourd'hui.";
			link.l1 = "Je soupçonne que je sais de qui cela vient. Merci et à bientôt.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Une délicieuse liturgie, n'est-ce pas, Charles ? Je suis sincèrement heureux pour vous ! De ma part et de tous les citoyens de Basse-Terre - je vous adresse nos félicitations à vous et à votre... charmante épouse. Vous formez un couple merveilleux ! Puissiez-vous vivre heureux pour toujours !";
			link.l1 = "Merci, Votre Grâce. Heureux que cela vous ait plu.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Quel service merveilleux, monsieur de Maure, tout simplement merveilleux ! Et la mariée est si... originale dans cette tenue. Au nom de tous les habitants de notre ville - acceptez mes plus sincères félicitations ! Je vous souhaite de nombreuses années de bonheur à venir !";
			link.l1 = "Merci, Votre Grâce.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Si charmant - vous et votre épouse, monsieur de Maure, aviez l'air si inhabituel ! Cependant, vous êtes un homme inhabituel. Je vous souhaite une longue et heureuse vie de famille. Puissiez-vous vivre heureux pour toujours !";
			link.l1 = "Je vous suis très reconnaissant, Votre Grâce.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Pour le bien de votre mariage, cela valait la peine de traverser les Caraïbes ! Félicitations, capitaine, de la part des habitants de toutes les colonies anglaises ! Vous et votre fiancée, pardonnez-moi, déjà épouse, formez un couple merveilleux !";
			link.l1 = "Merci pour la visite et pour vos aimables paroles, Colonel !";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Et que fait ce dandy marié sur ma plage de pirate, hein ?! Dites-moi, monsieur, qu'avez-vous fait de mon vieil ami - le rude pirate Charlie Prince ?";
					link.l1 = "Charlie Prince est mort, tu t'en souviens, Marcus... Ha-ha-ha viens ici, démon des mers ! Je suis content de te voir ! Comment ça va les gars ici, tout le monde est rassemblé ?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "Et que fait ce dandy marié sur ma plage de pirates, hein ?! Dites-moi, monsieur, qu'avez-vous fait de mon vieil ami - le rude capitaine Charles de Maure ?";
					link.l1 = "Ahoy, Marcus, je suis content de te voir aussi! Comment ça va ici, vous êtes-vous tous rassemblés?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "Et que fait ce dandy marié sur ma plage de pirates, hein ?! Dites-moi, monsieur, qu'avez-vous fait de mon vieil ami - le dur capitaine Charles de Maure ?";
				link.l1 = "Ahoy, Marcus, je suis content de te voir aussi ! Comment allez-vous ici, est-ce que tout le monde est rassemblé ?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Oui, le Diable de la Forêt est arrivé hier seulement et a aussitôt commencé à commander - donc les invités sont là et tout est prêt pour la célébration. Ton bâtiment a été aperçu près des récifs, et les gars n'ont pas pu résister - ils se sont précipités dans la taverne et, très probablement, ils ont déjà ouvert ce tonneau de Hawk. Dépêche-toi, peut-être avons-nous encore une chance de boire un verre - Nathaniel s'est vanté que c'était une sorte de rhum spécial !";
			link.l1 = "Maintenant, c'est comme ça qu'on fait - du navire directement à la fête ! J'attendrai ma meilleure moitié et nous serons juste derrière toi, Marcus !";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Oui, le Diable de la Forêt est arrivé hier seulement et a aussitôt pris les commandes - alors les invités sont là et tout est prêt pour la fête. Votre navire a été repéré près des récifs, et les gars n'ont pas pu se retenir - ils se sont précipités dans la taverne et, très probablement, ils ont déjà ouvert ce tonneau de Hawk. Dépêche-toi, peut-être avons-nous encore une chance de boire un verre - Nathaniel s'est vanté que c'était une sorte de rhum spécial !";
			link.l1 = "Maintenant, c'est comme ça qu'on fait - du navire directement à la fête ! J'attendrai ma meilleure moitié et nous te suivrons de près, Marcus !";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Mariee a Charles de Maure - je n'arrive toujours pas a m'y habituer... D'abord Svenson, maintenant toi - et apres? Le pasteur Marlow, ou Jacques le Gentilhomme?";
			link.l1 = "Tu as oublié les Hawks. Et toi, Marcus ? Pas fatigué d'être un loup de mer solitaire ?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie et Nathan sont une affaire de longue date - je m'y suis déjà fait, mais tu m'as surpris, il n'y a rien à dire ! Cependant, la pupille du Diable des Forêts est belle - il n'y a rien à dire, prête à utiliser un mot et un pistolet à tout moment, et elle peut affronter n'importe quelle tempête. Il est peu probable que tu puisses te trouver une femme plus digne. Tu es un veinard, capitaine - prends soin d'elle !";
			}
			else
			{
				dialog.text = "  Dannie et Nathan sont un cas de longue date - je me suis déjà fait une raison, mais tu m'as surpris, il n'y a rien à dire ! Bien que, comme j'ai entendu dire, ta Mary en sait beaucoup sur les épées et qu'elle sait clairement les manier - mes respects ! Une vraie compagne de guerre. Je vais te confier un secret, pour une telle fille, je pourrais moi-même revoir mes convictions de célibataire. Tu es un veinard, capitaine - prends soin d'elle !";
			}
			link.l1 = "Je sais, elle est un miracle et je suis de nouveau au septième ciel de bonheur - tout comme ces jours où nous nous sommes rencontrés pour la première fois !";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Eh bien, un toast!... Pour l'amour!... Mais pas pour celui qui nous pousse au-delà du seuil et vers l'horizon!... Mais pour celui qui nous attend à ce seuil! Pour l'amour, celui qui nous fait revenir vers lui, même depuis le bout du monde et des montagnes d'or! Vivre avec lui et être heureux!";
			link.l1 = "Superbe toast, Marcus, merci !";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "A la tienne, pour ton mariage, camarade !";
			link.l1 = "Merci, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques ?  Cela n'augure rien de bon...";
			link.l1 = "Marcus, penses-tu...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Il n'y a pas de temps ! Ils sont derrière les portes ! Tout le monde, aux armes !";
			link.l1 = "Nous y voilà !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Je ne me souviens pas de la dernière fois où je me suis autant amusé à une fête ! Ce n'est pas encore fini ! Entends-tu cela ? Quelqu'un tire dehors ! Laissons les rues jonchées de leur sang !";
			link.l1 = "Attendez ! Qui diable sont-ils !? Et que diable veulent-ils vraiment ?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitaine marié de Maure, rarement ai-je rencontré des raisons plus sincères pour un toast. Levez un verre - ce n'est pas une boisson au chou ordinaire. C'est infusé avec du thé noir d'Inde orientale et assaisonné avec de véritables épices persanes !";
			link.l1 = "Et j'ai réfléchi à pourquoi ça brûle dans ma gorge comme si j'avais bu du plomb en fusion. Eh bien, Nathan, santé...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Attendez, d'abord un toast ! Hé messieurs, levez vos chopes ! Aujourd'hui, notre ami et associé Charles de Maure entre dans la voie de la vie familiale. Acceptez de notre part les plus sincères condoléanc... oh, Dannie s'il te plaît, pose le pistolet ! Félicitations, bien sûr ! Désormais, vous êtes les voiles du même navire, alors guidez-la à travers toutes les tempêtes vers les rivages les plus fertiles !";
			link.l1 = "Merci, Nathan, sincèrement. Toi et Danielle êtes un exemple à suivre pour nous.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Cela fait plaisir à entendre. Ma femme et moi ne sommes peut-être pas le meilleur couple du monde, mais nous sommes heureux ensemble, et tu as fait tant pour nous, donc si tu me demandes, tu fais partie de ma famille, et je serai là pour toi chaque fois que tu auras besoin de moi. Sois heureux, et prends un verre, je te prie !";
			link.l1 = "Alors buvons ! Oh... ce rhum devrait avoir sa place dans l'arsenal de la Sainte Inquisition. Nom d'un chien ! Ça brûle tout le long... aghhh ! Ouf !... J'aime ça !";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Tu ressembles tellement à Dannie et moi il y a vingt ans !";
			link.l1 = "Encore une tasse, Nathan !";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Quoi !? Jan t'a envoyé dans les caves pour apporter du vin ? Allons nous promener, je vais t'aider un peu, et l'air frais te fera du bien.";
			link.l1 = "Mais où sont Dannie et "+sld.name+"? Jan m'a dit qu'ils étaient allés discuter.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Oui, Dannie sait que la présence même de la meilleure fille d'armes ne donnera toujours pas aux messieurs de la chance du temps pour se détendre pleinement. Alors ils ont écouté tous les compliments qu'ils ont reçus et sont allés à la résidence pour laisser les gars s'amuser.";
			link.l1 = "Eh bien, alors, en avant ! J'ai réussi à boire quelques chopes, mais que le diable m'emporte, il est vraiment temps de se saouler comme il faut !";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Alors, voici le coffre. Nous prenons autant que nous pouvons porter et nous retournons, jusqu'à ce que ce vieux grognon nous enferme ici.";
			link.l1 = "Tu exagères, Nathan. Il n'est pas si mauvais... Attends, as-tu entendu ça?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan a probablement trouvé plus de gars et les a envoyés pour nous aider. Putain !";
			link.l1 = "Allez, les bouteilles se cassent pour la chance. Prends-en une de plus et allons-y.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Que diable se passe-t-il, qui sont ces salauds ? Comprends-tu quelque chose, Charles ?";
			link.l1 = "Je ne sais pas, Nathan, mais l'un d'eux est parti chercher de l'aide, et il me semble entendre plus de pas. Nous devons retourner à la taverne !";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Nous avons abattu ces salauds, mais les canons grondent depuis la mer, entends-tu ? Nous avons seulement deux équipages prêts pour la bataille, sur la frégate de Marcus et la corvette de Jan. Moi, Dannie et d'autres avons débarqué nos gars - mariage après tout - donc le Centurion est hors jeu. Et ton navire ? Nous devons décider quoi faire et vite !";
			link.l1 = "J'ai débarqué la moitié de l'équipage, j'espère que le reste est sobre. Mais d'abord, je dois trouver ma femme et m'assurer qu'elle va bien.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Oui, Dannie est également introuvable. Alors, nous agissons ainsi - Tyrex et Svenson se sont déjà précipités vers le port, ils atteindront leurs navires en bateau. Nous allons à la résidence pour les épouses, les autres - qu'ils organisent la défense sur le rivage. Peux-tu envoyer quelques-uns de tes officiers pour rassembler les gens sur ton navire ? Un peu d'aide ne fera évidemment pas de mal.";
			link.l1 = "Bien, tout le monde, en avant ! Chaque seconde compte !";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Plus vite, à l'étage ! Dannie et "+sld.name+" doit être là ! Et si ces salauds leur font du mal...";
			link.l1 = "N'y pense même pas ! Là-haut ! Allons-y !";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Merde ! Ton camarade, il s'est précipité droit sur le canon pour que ce salaud ne tire pas sur les filles !";
			link.l1 = "Et il a pris une balle... Attends, Nathan... il respire ! Il est encore en vie ! Bon sang, j'ai besoin de Gino ! "+sld.name+", chéri, comment vas-tu ?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nous allons bien, Charles ! Je vais la détacher. J'entends des coups de feu dans le port - toi et Nathan devez y aller, sinon Barbazon détruira tous nos navires. Ne perdez pas de temps !";
			link.l1 = "Je vais trouver Gino et l'envoyer ici, il aidera... il doit le faire ! "+sld.name+", ma chère, reste ici, prends soin de lui, vous deux.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, dépêche-toi ! quoi que tu décides, le temps vaut maintenant son pesant d'or ! Si les navires de Jacques atteignent le rivage, tout sera en vain !";
			link.l1 = "Oui, je sais. Salaud de merde !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Plus vite, nous n'avons pas de temps pour bavarder !";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Merde! Pardonne-moi Charles. Nous étions coincés à l'étage, il y avait une douzaine de ces salauds... C'est dommage que je ne sois pas arrivé à temps, mais je vois que tu t'es occupé de la situation de la meilleure façon possible.";
			link.l1 = "Je ne peux pas dire que ce fut facile, mais, putain, j'ai pris un grand plaisir à tuer ce 'gentilhomme' ! Il est temps de débarquer, Nathan, nos hommes nous attendent là-bas !";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Oui, nous devons rendre visite à ton garçon indien, finir ici et aller à Sharptown.";
			link.l1 = "Tu as raison, je suis derriere toi.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Soit dit en passant, nous avons trouvé Marcus ! Il était dans la cale, ligoté et inconscient.";
			link.l1 = "Il est vivant ?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Il est en piteux état, mais il va s'en sortir. Tyrex est plus fort qu'un clou pour un cercueil, alors ne t'inquiète pas, il a déjà été transféré sur ton navire et a demandé un sabre.";
			link.l1 = "Enfin, de bonnes nouvelles ! Très bien, finissons ici et retournons.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Bonjour, Charles. Laisse-moi te regarder - tu es devenu plus beau, rien à redire ! Presque comme Nathan, il y a dix ans ! Entre, ne reste pas sur le seuil, tout le monde n'attendait que toi !";
			link.l1 = "Merci, Dannie, je suis très heureux de te voir ! Je viendrai te voir toi et Nathan un peu plus tard, et ensuite nous parlerons !";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, assieds-toi - Nathan et moi sommes si heureux pour toi ! Marcus, Jan et mon mari ont préparé quelque chose pour toi - mais les cadeaux attendront. Pour l'instant, laisse-moi te féliciter et te souhaiter bonheur ! Ta bien-aimée est vraiment un miracle ! Dis-moi, tu n'as pas réussi à la faire porter une robe blanche là-bas en Martinique, n'est-ce pas ?";
			link.l1 = "Merci, Dannie. Oui, ça a été drôle avec la robe - je suis sûr que dans la haute société notre mariage a suscité de nombreuses rumeurs scandaleuses. Tout le monde a honnêtement détourné les yeux et a fait semblant que rien d'extraordinaire ne se passait. Les manières et tout ça - mais je me fiche des commérages, je l'aime et c'est le plus important.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Tu as tout à fait raison ! Moi aussi, j'ai marché jusqu'à l'autel, avec une épée et une paire de pistolets derrière l'écharpe. Mais c'était à Port Royal, bien avant qu'elle ne devienne une résidence coloniale digne. C'était tellement amusant à cette époque, encore plus que sur Tortuga sous Levasseur et personne n'était surpris... eh. Cependant, je bavarde tout le temps - va faire le tour des invités, tout le monde t'attend ici, donne-moi juste une étreinte !";
			link.l1 = "Ah Dannie, comment pourrais-je même te refuser ha-ha ! Tu ne peux même pas imaginer à quel point ma femme et moi sommes heureux de vous voir tous !";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Vous êtes un beau couple, Charles !";
			link.l1 = "Merci, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, il a raison... tu n'as pas le choix. Je ne crois pas en la clémence de Jacques le Bon, s'il s'occupe de Tyrex et du reste. Tu sais ce qu'il faut faire.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "N'écoutez pas lui ! Si le Kindman décidait de faire une telle folie, il n'épargnera personne !";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nous allons bien, Charles ! Je vais la détacher. J'entends des canons dans le port, toi et Nathan devez y aller, sinon Barbazon va couler nos navires comme des canetons dans un tonneau. Vous ne devriez pas perdre une minute !";
			link.l1 = "Je trouverai Gino et je l'enverrai ici, il aidera... il le doit, bon sang!"+sld.name+", ma chère, reste ici, occupe-toi de Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, non !!!";
			link.l1 = "Il saisit l'instant et se précipita vers le canon pour te couvrir, Dannie... "+sld.name+", chéri, comment vas-tu ?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Oui, Charles, il est vivant ! Le coeur bat à peine, mais il est vivant ! Que devrions-nous faire ?!";
			link.l1 = "Nous avons besoin de Gino, immédiatement ! Je vais le trouver et l'envoyer ici, il nous aidera... il le doit !";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, nous n'avons pas de temps ! Si les navires de Jacques atteignent le rivage, tout sera en vain ! Mon mari... il a fait ce qu'il devait. Maintenant, c'est à ton tour. Je resterai avec lui. Vous deux devriez partir et trouver Gino !";
			link.l1 = "Oui, je sais. Putain de salaud, il paiera pour ça !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Enfin vous voilà ! Tout le monde va bien ?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Nous allons bien, Dannie, ne t'inquiète pas. Jacques est mort, ses navires sont au fond. Comment va Tichingitu ?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Nous allons bien, Dannie, ne t'inquiète pas. Jacques est mort, ses navires sont au fond. Comment va Nathan ?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Il va bien ! Ton médecin italien est un génie ! Nathan dort à l'étage, mais, selon Gino, rien ne le menace. Une semaine ou deux au lit, du vin rouge, et, comme il a dit 'la visite d'une dame bien disposée à son égard' ahem... En général - tout va bien, tu nous as encore sauvés, Charles, comment puis-je te remercier ?";
				link.l1 = "C'est Nathaniel qui a sauve ma femme et toi. Et je lui en serai toujours redevable. Tu ne peux meme pas imaginer a quel point je suis heureux d'entendre qu'il se remet. Laisse-le se reposer, je te verrai plus tard.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Il va bien, la balle est passée de part en part, et notre chirurgien du 'Centurion' n'était pas loin. Il se cachait de tout ce foutoir. Donc Nathan vivra, quelques semaines au lit - une petite broutille !";
				link.l1 = "Dannie, il a protégé ma femme et toi d'une balle et je lui serai éternellement redevable pour cela. Tu ne peux même pas imaginer à quel point je suis heureux d'entendre qu'il se rétablit. Laisse-le se reposer, je viendrai te voir plus tard.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Bien sûr ! Mais je dois te quitter, je dois aller retrouver mon mari... Cela ne te dérange pas si nous empruntons ton ami ? Quand Nathan ira mieux, je l'emmènerai moi-même à Antigua. Le Centurion a miraculeusement survécu, il lui suffit de recruter un nouvel équipage.";
			link.l1 = "Très bien, Dannie, dis bonjour à Gino et Nathan. Je dois y aller.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Bien sûr, Charles, mais... J'ai de mauvaises nouvelles. Cet Italien, Guineili, qui était à ton mariage... Son corps a été trouvé dans une chambre de la taverne. Je suis... Je suis désolé, Charles.";
			link.l1 = "Quoi ? Gino ?! Non ! Comment ?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Je ne sais pas, probablement l'un de ces salauds qui sont passés par les catacombes et ont attaqué la ville. Apparemment, ils s'y cachaient, attendant le bon moment pour s'échapper, et l'ont trouvé...";
			link.l1 = "Merde! Non, je n'y crois pas...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Je suis désolé, Charles. C'était un vrai bain de sang, et il n'était pas un combattant... Si tu veux, nous enverrons son corps à ton navire, ramène-le chez toi et enterre-le comme il se doit. Je suis vraiment désolé...";
			link.l1 = "Merci, Dannie. Donne l'ordre de charger le corps sur un navire. Je dois y aller maintenant... Je dois réfléchir. Et passe le bonjour à Nathan.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Il va bien ! Votre médecin italien est un génie ! Il dort dans la chambre à l'étage, et Gino veille sur lui. Il dit 'une semaine ou deux et il ira bien'.";
				link.l1 = "Excellente nouvelle ! Je suppose que je ne peux pas lui rendre visite pour l'instant ?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Je suis tellement désolé, Charles. J'ai retrouvé notre chirurgien du Centurion, mais il n'a rien pu faire... Ton ami est mort il y a quelques heures.";
				link.l1 = "Tichingitu?! Non! Je n'y crois pas !!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Non, l'Italien a strictement interdit de le déranger, laissez-le se reposer, et Gino devrait se reposer après toutes ces inquiétudes. J'ai même dit "+sld.name+"pour sortir se promener quand nous avons découvert que tout allait bien se passer\nEt une chose de plus... ton ami, il m'a protégé de la balle. Je ne sais même pas comment le remercier, dis-lui que dorénavant il fait aussi partie de notre famille, et toi - tu nous as sauvés encore une fois, Charles !";
			link.l1 = "Tout est bien qui finit bien, Dannie. Va voir Nathan, il t'attend, et je vais prendre une petite pause ici et chercher mon "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Désolé, j'ai fait tout ce que je pouvais, et "+sld.name+", aussi. Il nous a protégés de cette balle, et je n'oublierai jamais cela, crois-moi.";
			link.l1 = "... Il y a longtemps, il avait dit qu'il mourrait pour moi... Je suppose qu'il n'a jamais su qu'il sacrifierait sa vie pour nous tous... et maintenant il est un héros et je me souviendrai de lui comme rien de moins... Où est "+sld.name+"? Est-elle d'accord ?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Je ne saurais le dire... Je veux dire, physiquement oui. Mais... vous savez... Elle a dit qu'elle était sortie se promener, pour se vider l'esprit. Elle vous a probablement vu amarré et reviendra bientôt.";
			link.l1 = "Maudits sois-tu Jacques Barbazon... On aurait dû le tuer avant !";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Attends... ce n'est pas tout encore. Cet Italien, Guineili, oui? Ce jeune homme discret. Il était... son corps a été trouvé dans une taverne... Je ne sais pas, probablement un de ces salauds qui ont traversé les catacombes et attaqué la ville. Apparemment, ils s'y cachaient, cherchant un moment pour s'échapper, et l'ont trouvé...";
			link.l1 = "Et Gino aussi ?! Aujourd'hui est vraiment un jour de pluie...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Je suis désolé, Charles... Si tu veux, nous enverrons leurs corps sur ton navire, ramène les gars chez eux et enterre-les comme il se doit. Je suis vraiment désolé...";
			link.l1 = "Merci Dannie. Fais-le... Je devrais y aller... J'ai besoin... de réfléchir.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, peux-tu imaginer combien de coeurs de jeunes filles tu as brisés avec ce mariage ? Oui, la moitié des filles de l'archipel ont dû pleurer après ton mariage, haha !";
			link.l1 = "Que puis-je faire - je n'avais besoin que d'une seule et je l'ai eue. Mais il est trop tôt pour que les filles soient bouleversées, car elles t'ont encore, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "Et c'est bien vrai! Nous finirons ici et je m'occuperai d'eux immédiatement, bon sang! Allez, Charles, buvons à ta chance et à la vie de famille. Alors, comme on dit, ils vécurent heureux jusqu'à la fin des temps!";
			link.l1 = "Merci mon ami !";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "À une vie de famille heureuse, ha-ha!";
			link.l1 = "À la tienne !";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, peux-tu même imaginer combien de coeurs de filles tu as brisé avec ton mariage ? Oui, la moitié des filles de l'archipel ont dû pleurer après ton mariage, haha !";
			link.l1 = "Que puis-je faire - je n'avais besoin que d'une et je l'ai eue. Mais il est trop tôt pour que les filles soient contrariées, car elles ont encore toi, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "Et c'est vrai ! On finit ici et je m'en occupe immédiatement, bon sang ! Allez, Charles, buvons à ta chance et à ta vie de famille. Alors, comme on dit, ils vécurent heureux jusqu'à la fin des temps !";
			link.l1 = " Heureux pour toujours !";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Pour une vie de famille heureuse, ha ha !";
			link.l1 = "Grand toast !";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, toi aussi tu t'es marié et es devenu ennuyeux, comme notre vieux Nathan ! Les aventures torrides et tout le reste sont maintenant du passé, hein ? Bon père de famille !";
			link.l1 = "Continue d'attendre, Bernard ! Ma femme n'est pas de celles qui s'ennuieraient assises sous la fenêtre d'une épave familiale ! La seule chose qui changera, c'est la plénitude des bourses des filles de joie d'ici jusqu'à Curaçao !";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Pas une grande perte, je dis ! Mieux vaut avoir une pièce d'or qu'un sac de centimes. Allons boire un coup ! Santé à toi et ta femme ! Garde ton or en sécurité et sois heureux !";
			link.l1 = "Merci Bernard. Oh, c'est un rhum vraiment fort. Ouf !";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "À ta promise, je veux dire, déjà une épouse !";
			link.l1 = "Merci!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Tu arrives juste à temps, Charles, merci !";
			link.l1 = "Quel est le plaisir ici ? Je pensais que vous chargiez déjà sur les navires dans le port.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus m'a laissé organiser une défense sur le rivage. Nous manquons de monde, les gars dans le port ont besoin de poudre à canon. Je pensais passer, prendre quelques barils ... et puis ces voyous. Hah, ils se sont cachés, je suppose, voulaient attendre ou voler quelqu'un. Et je suis encore plein du rhum de Hawk, donc sans toi, je ne sais pas si je serais encore en vie ou non.";
			link.l1 = "Vous êtes toujours le bienvenu. Bien, Bernard, assurez-vous que la ville est sécurisée, et je devrais partir, restez prudent !";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitaine, permettez-moi de vous féliciter chaleureusement, vous et votre bien-aimée, en ce jour de bon augure ! Soyez heureux et prenez soin l'un de l'autre !";
			link.l1 = "Merci, Gino. Je suis content que tu aies décidé de venir ! J'espère que la couleur locale ne te dérange pas ?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "C'est... un voyage très instructif. Je dois dire - je n'ai pas quitté Antigua depuis longtemps, et dans cette société il n'est pas facile pour moi de me sentir à l'aise. Mais, tu as toujours su comprendre les gens, donc je vais essayer de rester calme, puisque je te fais confiance.";
			link.l1 = "Peut-être que tu as besoin de boire quelque chose de plus fort ? Détends-toi et trouve quelqu'un à qui parler ?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Merci, capitaine, j'ai assez de vin dilué. L'alcool, je dois vous avertir, n'est pas très bon pour le foie et peut-être le coeur. Quant aux conversations, j'ai essayé de discuter des propriétés curatives du Chirik-Sanango avec ce gentilhomme là-bas, il est aussi appelé Manaka. Les indigènes du Maine l'utilisent pour...";
			link.l1 = "Permettez-moi de deviner - ce gentilhomme n'a pas pu soutenir la conversation ? Gino, pour l'amour de moi et seulement aujourd'hui - essayez le rhum que Jan là-bas verse au comptoir. Si vous pouvez deviner tous ses ingrédients, Nathaniel Hawk, là-bas, sera extrêmement impressionné. Je suis sûr qu'il sera ravi d'être en votre compagnie ainsi que Svenson, l'homme au comptoir, tous deux respectent les gens instruits.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "À votre santé et à la santé de votre charmant époux !";
			link.l1 = "Merci, l'ami !";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Capitaine, c'est vous, Dieu merci ! Ces gens masqués, je les ai vus et je me suis caché ici, et ils ont essayé de défoncer la porte...";
			link.l1 = "C'est bon, Gino, personne ne te fera plus de mal. C'est une grande chance que je t'aie trouvé, j'ai besoin de ton aide. Mon ami est blessé - il a été touché, et il a perdu beaucoup de sang. Nous devons nous dépêcher !";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Tiré... du sang... bien, capitaine. En venant ici, j'ai pris ma caisse de campagne avec tous les outils en cas de blessure. Conduis-moi à lui, je verrai ce qui peut être fait. Et ces... hommes masqués, peut-être ont-ils rôdé ailleurs ?";
			link.l1 = "Je suis sûr qu'ils étaient les derniers. Gino, il y a bataille dans le port et je dois y aller tout de suite. Tu dois te rendre à la résidence par toi-même, ce n'est pas loin. La grande maison est juste au coin - tu ne peux pas la manquer. N'aie pas peur - les rues sont pleines des nôtres, et dépêche-toi, je t'en prie !";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Capitaine, permettez-moi de vous féliciter chaleureusement, vous et votre bien-aimée, en ce jour de bon augure ! Soyez heureux et prenez soin l'un de l'autre.";
			link.l1 = "Merci, Gino. Je suis content que tu aies décidé de venir ! J'espère que le voyage s'est bien passé ?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Tout va bien, capitaine, merci de votre sollicitude. Je dois dire - je ne suis pas sorti d'Antigua depuis longtemps, et parmi l'élite je... ne me sens pas très à l'aise. Mais la raison de venir ne m'a pas laissé le choix. Au fait - le service était excellent, je suis très heureux pour vous deux ! La mariée dans cette tenue est charmante - est-ce une nouvelle mode ? Il semble que j'ai pris du retard sur la vie, mais ça me plaît, vraiment.";
			link.l1 = "La mode... En quelque sorte, oui, ou du moins, elle le deviendra bientôt. Très bien, amuse-toi, Gino, et si les interlocuteurs nobles te lassent, alors viens au port. Tout l'équipage est à la taverne. Les gars seront ravis de te voir.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Capitaine, Encore une fois, je vous félicite, vous et votre belle épouse ! Que vous ayez de longues et heureuses années ensemble !";
			link.l1 = "Merci, Gino. Je suis content que tu sois venu ! J'espère que la couleur locale ne te dérange pas ?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Cette société n'est pas facile pour moi de me sentir à l'aise. Mais, tu as toujours su choisir les gens, alors je vais essayer de rester calme, car je te fais confiance..";
			link.l1 = "Peut-etre que tu as besoin de boire quelque chose de plus fort ? Détends-toi et trouve quelqu'un à qui parler ?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Merci, capitaine, j'ai assez de vin dilué. L'alcool, je dois vous avertir, n'est pas très bon pour le foie et possiblement le coeur. Quant aux conversations, j'ai essayé de discuter des propriétés curatives du Chirik-Sanango avec ce monsieur, on l'appelle aussi Manaka. Les natifs du Maine l'utilisent pour...";
			link.l1 = "Permettez-moi de deviner - ce gentilhomme n'a pas pu soutenir la discussion ? Gino, pour l'amour de moi et seulement aujourd'hui - essaie le rhum que Jan là-bas verse au comptoir. Si tu peux deviner tous ses ingrédients, Nathaniel Hawk, là-bas, sera extrêmement impressionné. Je suis sûr qu'il sera ravi d'être en ta compagnie ainsi que Svenson, l'homme au comptoir, tous deux respectent les gens instruits.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Seul maintenant dans un pays étranger, me sentant étranger, en ce jour de fête éclatant, je languis doublement de mes proches";
			link.l1 = "Longway, jamais je n'aurais pensé que tu étais un maître des mots !";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Désolé, Capitaine, j'ai beaucoup réfléchi. Ce sont les paroles de Wang Wei - un poète qui a vécu à l'époque de la dynastie Tang qui a régné il y a longtemps dans ma patrie.";
			link.l1 = "Ces mots sont si beaux. J'espère qu'un jour tu reverras ta terre natale...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Est-il possible de garantir et de savoir que sous l'arche de mystérieuses dalles de pierre, il est impossible de trouver un passage en essayant, au-delà duquel se trouve la vallée d'U-lin ?'\nNon, Capitaine, vous le savez - Longway ne va pas rentrer chez lui. Maintenant, ici est ma maison et nous avons un grand événement ici aujourd'hui ! Je vous envoie mes meilleurs voeux à vous et à votre belle épouse ! Que votre bonheur soit aussi long que le fleuve Yangtze, parsemé de diamants d'étoiles, entre les perles de lotus.";
			link.l1 = "Merci mon vieil ami. Tes paroles ne sont pas moins belles que celles de Wang Wei.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Prenons un verre, Capitaine ! Ce rhum chasse la tristesse et ravive la joie aussi bien que le maotai.";
			link.l1 = "À ta santé, Longway !";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Superbe mariage, capitaine !";
			link.l1 = "Bois et amuse-toi !";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Tire-moi une mitraille en chaîne ! Tous nos gars te félicitent ! Comment s'est passé le service ?";
				link.l1 = "Tout va bien, Charlie ! maintenant je suis officiellement marié et respectable, et mon premier lieutenant est madame de Monper maintenant.";
			}
			else
			{
				dialog.text = "Frappez-moi avec une mitraille, un tel événement, capitaine ! Presque tous les barons de la Fraternité sont ici ! Je suppose que chaque puritain espagnol imagine l'Enfer ainsi ! Et le rhum, c'est quelque chose de spécial, mitraille à mon tonneau !";
				link.l1 = "Oui, les gens ici ne sont pas les plus respectueux des lois, mais nous ne sommes pas nous-mêmes des anges, Charlie, et chacun de ces gens m'est cher à sa manière.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "C'est merveilleux, mitraille à mon cul ! Capitaine, je veux dire, cette célebration est en votre honneur, enfin, je... je vous félicite, je veux dire... aussi... Bonheur et... enfin, je ne suis pas bon en discours. Mais vous devez savoir que nous vous aimons tous deux et que nous vous suivrons même en enfer, capitaine !";
				link.l1 = "Merci, vieil ami.";
			}
			else
			{
				dialog.text = "Attends, je veux dire... Qu'est-ce que je veux dire, mitraille à mon derrière ?! Capitaine, je voulais dire que ce jour est en votre honneur, enfin, je... je vous félicite... et aussi... je vous souhaite du bonheur et... et pardon capitaine, je suis peut-être un peu trop ivre pour tenir un discours, mitraille à mon cou, cela fait un moment que je ne suis pas à jeun ha-ha-ha !";
				link.l1 = "Hah! C'est bon... merci, vieil ami.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah ! Et oui, capitaine, acceptez ceci, s'il vous plaît. Pour vous et votre dame. J'ai gardé ces pierres pour un jour de pluie... Je comprends que vous ne manquez pas d'or, mais elles ne seront pas superflues, n'est-ce pas ?";
			link.l1 = "Charlie, tu es vraiment une âme généreuse, et ces émeraudes seront magnifiques dans les boucles d'oreilles de famille de madame de Monper !";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Eh bien, trinquons à cela, une mitraille à mon... hm. Soyez juste heureux, vous et votre belle, capitaine !";
			link.l1 = "Nous le ferons, Charlie !";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Superbe mariage, capitaine !";
			link.l1 = "Bois et amuse-toi !";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Je n'aurais jamais pensé, capitaine, que je vous verrais marié. Habituellement, le chemin que nous avons choisi mène sur une voie solitaire droit vers une tombe solitaire. Dans ma mémoire, vous êtes le premier à en sortir. Cela vaut bien un toast supplémentaire, n'est-ce pas ?";
			link.l1 = "C'est ça, l'ami! Et vraiment, je suis heureux que cette partie de ma vie soit derrière moi. À la tienne!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "À votre santé et à votre longue et heureuse vie ensemble ! Sacrebleu, en vous regardant, je me rappelle que moi-même ai été marié autrefois.";
			link.l1 = "Toi? Marié? C'est intéressant ce que tu me dis là! Mais que s'est-il passé?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Quoi, tu penses que j'ai toujours été un vieux cyclope sentant la poudre et le sang, capitaine ? Mais non. Madame Tonzag elle... elle m'aimait, je suppose. Mais alors, une histoire désagréable est arrivée. Dans laquelle le couple Tonzag est mort et seul le Chauve Gaston avec ses cicatrices a réussi à survivre.";
			link.l1 = "Je suis désolé, Hercule, je ne savais pas...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Oublie ça, capitaine, cette histoire s'est passée il y a longtemps. Mais maintenant, en vous regardant, je pense que mon histoire peut encore avoir une bonne fin. Alors, buvons à cela !";
			link.l1 = "Laisse-nous, compagnon. Tu sais - depuis le jour où je t'ai rencontré, je t'ai toujours regardé comme je regarderais mon propre père, alors peut-être qu'un jour tu auras l'occasion d'être un grand-père. De toute façon, à la tienne ! Je dois m'occuper du reste, nous parlerons plus tard.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Grande fête, Capitaine !";
			link.l1 = "Bois et amuse-toi !";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Voici notre capitaine ! Félicitations, vous et votre épouse formez un couple magnifique ! Puisse votre vie être un long fleuve tranquille !";
			link.l1 = "Merci, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "On dirait que tu es trop sobre pour ton propre mariage, capitaine. Voudrais-tu y remédier? J'ai pris une bouteille de xérès excellent au bar. Le mélange avec le rhum local passe parfaitement !";
			link.l1 = "Je voudrais bien, mais quelqu'un doit garder un oeil sur les choses ici. Sinon, en "+sTemp+"   non seulement la taverne manquera quand le matin viendra.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Une nourriture excellente et un rhum excellent, capitaine ! À votre santé et à celle de votre jeune épouse !";
			link.l1 = "Merci !";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Jeunes gens, pourquoi entrez-vous par effraction, puis-je vous demander ? Le chantier naval est fermé, cela ne se voit-il pas ? Revenez demain.";
			link.l1 = "Maître, je suis désolé de vous déranger, nous allons juste passer par les cachots. Il y a des fournitures pour le mariage, la taverne est presque à court de boissons.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure et Nathan Hawk en personne ! Vous célébrez un mariage, n'est-ce pas ? Très bien - allez chercher votre boisson. Les jeunes doivent s'amuser - c'est la loi en tout temps. Mais ne faites pas cliqueter les bouteilles en revenant - je vais dormir !";
			link.l1 = "Merci, maître, nous serons aussi silencieux que la rivière la plus calme.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Allez, ne reste pas planté là, va ! Eh bien, capitaine, êtes-vous satisfait de tout ?";
			link.l1 = "... ";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Qu'est-ce que c'est que ce bordel ?! Jacques a dit 'Personne ne descend ici' ! Hugo - retourne en arrière, appelle les autres, nous allons dégager le passage. Tuez-les, les gars !";
			link.l1 = "Merde !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Les gars, oubliez les coffres, nous avons des invités !";
			link.l1 = "Je pensais que des salauds comme toi avaient été tués avec Jackman. Très bien, finissons-en !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Putain... Nous avons été découverts ! Alerte !";
			link.l1 = " Dégage de mon chemin, connard ! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, bonsoir, ou est-ce déjà presque le matin ? Entrez, prenez un siège.";
			link.l1 = "Angerran De Chievous! Voilà bien quelqu'un que je ne suis pas surpris de voir ! L'insignifiant, capable de ne se battre qu'avec des femmes ! Tu les as attachées aussi ?! Maintenant, je vais finir ce que j'ai commencé lors de ce duel à la Martinique !";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Calme-toi, jeune homme, tu vois ce pistolet ? Il y a deux canons. Peut-être que je suis mauvais à l'escrime, mais je tire assez précisément - baisse ton épée, ou tu manqueras quelques belles dames, je t'assure.";
			link.l1 = "Salaud... Que le diable t'emporte.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "Et toi, monsieur pirate, pose aussi ton arme, comme ça, oui. Et maintenant - assieds-toi, tu peux verser le vin - là-bas sur la table. Nous devrons attendre un peu jusqu'à ce que monsieur Barbazon ait fini de démolir les navires de tes amis, les barons pirates. Ensuite, nous déciderons comment toi et moi réglerons nos... hm, différends.";
			link.l1 = "Regler les differends? Et comment? Voulez-vous un duel?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Ne sois pas si drôle, Charles. Toi et madame Botot m'avez causé beaucoup d'ennuis, et j'ai l'intention de vous rendre la pareille. Bien qu'elle m'ait causé bien plus de problèmes que toi... cependant, si toi et l'imposant monsieur pirate restez tranquilles, alors je vous donne ma parole d'honneur - vos épouses resteront en vie. Je pense que dans les colonies espagnoles du Maine, de tels esclaves ont de la valeur. Même officieusement. Mais c'est toujours la vie, n'est-ce pas ?";
			link.l1 = "Angerran, tu es un lâche, un bâtard et... Merde, il n'existe pas encore de mots adaptés pour toi dans aucune langue !";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Tu le sais, tu n'as pas le choix. Je ne peux que promettre que ce sera rapide. Alors, si tu aimes ces femmes - conduis-toi bien, sauve leurs vies et allège ton sort. Et oui - verrouille la porte si ce n'est pas trop difficile pour toi. Merci.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Telles dames belliqueuses. Je vous demanderai quand même d'être prudentes. Je n'ai jamais aimé tuer des femmes.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Merde...";
			link.l1 = "Crève, salaud !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Capitaine Charles de Maure, baron Hawk - quelle agréable surprise ! Permettez-moi de me présenter - Mauritz Dussak, c'est mon nom.";
			link.l1 = "Sors de mon chemin, salaud ! Ou est ma femme ?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Calmez-vous, messieurs ! Voyez ce pistolet ? Il y a deux canons. On m'a surnommé ainsi pour une raison - j'aime les sabres, bien sûr... mais je tire aussi bien, croyez-moi. Déposez vos épées, ou vous manquerez quelques-unes de vos dames !";
			link.l1 = "Je vais t'égorger comme un cochon, racaille...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Mais vous serez déjà veuf. Vous ne le voulez pas ? Alors calmez-vous et déposez votre arme. Baron Hawk, je vous prie, fermez la porte. Et nous allons nous calmer et attendre un peu pendant que Jacques Barbazon là-bas dans le port finira les chefs des Frères.";
			link.l1 = "Et ensuite? On se fait un câlin et on part ensemble au coucher du soleil ?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Je ne pense pas. Pour ta captivité, Jacques me couvrira d'or, avec un peu de chance, peut-être deviendrai-je baron. Quant à tes femmes, peut-être les laisserons-nous partir, mais pour ce qui est de toi - hélas... Si tu as de la chance, je demanderai le droit de te tuer personnellement, capitaine. Tu es un escrimeur célèbre - ce serait intéressant de te mettre à l'épreuve. Tu sais, je me considère aussi comme un maître.";
			link.l1 = "Un maître du cambriolage nocturne et de l'attache de femmes à moitié endormies ? Tu es un ver, de surcroît - un ver puant !";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Ecoutez, madame, je n'ai jamais tué de femmes, ne me faites pas commencer, d'accord? Vous énervez le capitaine et votre mari... Nom de Dieu!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Putain...";
			link.l1 = "Crève, salaud !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Satané français, n'y avait-il pas de sabre ou de balle?!";
			link.l1 = "Tu sais, Jacques, j'ai les deux pour toi. Honnêtement, je regrette presque de t'avoir laissé en vie quand j'ai découvert tes manigances avec Jackman. Mais, maintenant je vais arranger ça.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Tu es si courageux seulement quand tu marches avec une bande de tes gars ? Changeons la situation ! Je m'occuperai des barons plus tard, mais toi, tu ne sortiras pas d'ici vivant, rat !";
			link.l1 = "Attendu...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Capitaine, à l'aide, ce sauvage, il m'a enlevée ! Je... je dois rentrer chez moi - l'oncle a probablement déjà retourné toute la ville !";
			link.l1 = "Calmez-vous, beauté, tout ira bien. Écartez-vous, il faut que je parle avec votre 'sauvage'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Merci, capitaine ! Vous m'avez sauvé ! Quand je me suis réveillé ce matin sur cette plage, je... ne peux pas croire que j'allais épouser ce sauvage, il...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Oui, le matin est un marteau sévère pour le cristal d'espoir de la nuit. Comprenez. Mais il est de la tribu Muscogue, et il vit selon les lois sévères de sa terre. Il t'a volée avec ton consentement, et vous avez passé la nuit ensemble. Alors maintenant, aux yeux de ses Dieux, vous êtes mari et femme. Allons préparer tes affaires, et je réglerai la question de la rançon avec ton oncle.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Je suis désolé pour cela. Tichingitu vit selon les lois de sa tribu, mais c'est une bonne personne. S'il vous plaît, oubliez cette histoire d'enlèvement.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Femme? Aux yeux de ses dieux?! Non, capitaine, je vous en supplie, sauvez-moi de cela ! C'était juste... une aventure, il était si galant et gentil, pas comme ces rustres... Mais me marier ? Je suis trop jeune pour m'installer dans une cabane avec un sauvage !";
			link.l1 = "Il est mon officier et mon meilleur ami, alors ne t'inquiète pas, je le paie bien, et tu auras la meilleure cabane que tu aies jamais voulue. Tichingitu est un bon chasseur, il te procurera de la nourriture, et tu accoucheras et gardereras des enfants.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Des enfants ? Procurer de la nourriture ?! Non capitaine, je vous en prie, ne me faites pas cela, je vous implore !";
			link.l1 = "Eh bien, peut-être que je peux le convaincre. Mais ce ne sera pas facile. La tribu Muskogue prend ces choses très au sérieux, si quelqu'un découvre qu'il a volé une squaw et ne s'est pas marié...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Tu dois essayer, s'il te plaît ! Je ne dirai rien à personne, personne ne saura ! Je mentirai à l'oncle, ce ne sera pas la première fois !";
			link.l1 = "Très bien, tu devrais partir, belle squaw. Je vais essayer de tenir mon ami à l'écart.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Il m'a volé comme... comme une chèvre d'une grange ! Je le dirai à tout le monde ! L'oncle le tuera ! Il est terrible en colère ! Il avait l'habitude de piller les navires espagnols - on ne plaisante pas avec lui !";
			link.l1 = "Très bien, chut, belle dame, chut. Peut-être que vingt mille 'raisons' de lui pardonner seront plus éloquentes que mes mots ? Ou devrais-je les donner à votre oncle, comme une rançon pour une épouse ? Après tout, tout le monde est sur l'île, n'est-ce pas ? Demain, nous pourrons organiser un autre mariage...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Non non, capitaine, attendez ! Vous m'avez convaincu. Je trouverai quelque chose pour que mon oncle ne soit pas en colère. Adieu ! Et adieu à toi, mon étalon des plaines lointaines ! Reviens me voir la prochaine fois que tu passes...";
			link.l1 = "C'est ça. Heureux que nous soyons d'accord. Cours chez toi, beauté.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Eh bien, Capitaine, êtes-vous satisfait de tout? Le meilleur rhum, des côtelettes d'agneau, des jambons de porc et même d'excellents vins de mes stocks personnels pour votre ami scientifique ! Et - mes félicitations à vous et à votre belle épouse !";
			link.l1 = "Merci ! Je dois admettre que tu as tout organisé à la perfection. J'espère que tu as assez de stocks de rhum dans tes caves, le matin est loin.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Ne vous inquiétez pas pour ça, si les tonneaux montrent le fond, j'enverrai un assistant à l'entrepôt du port. Amusez-vous, monsieur, et ne vous inquiétez de rien.";
			link.l1 = "D'accord, "+npchar.name+"  Alors j'irai voir mes invités. ";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Que souhaitez-vous, capitaine ? Cotes grillees, jambon fume ou poitrine ? Peut-etre du vin pour votre meilleure moitie ?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("À la santé du capitaine et de sa femme !","Puissiez-vous vivre heureux pour toujours, capitaine !","Longue vie et bonheur à vous deux !"),LinkRandPhrase("Hip hip hourra au capitaine et à sa beauté!","La chance accompagne le capitaine et son épouse toute leur vie !","Bon vent à ta vie de famille, capitaine !"));
			link.l1 = LinkRandPhrase("Merci !","Merci !","À la tienne !");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou? Tu voulais jouer au boucher? Tous les pirates sont en colère contre toi, mon gars, alors tu ferais mieux de quitter cet endroit.","Il semble, l'ami, que tu sois devenu fou. Tu voulais te dégourdir un peu les mains? Sans vouloir t'offenser, mais tu n'as rien à faire ici. Dégage!");
				link.l1 = RandPhraseSimple("Écoute, je veux arranger la situation...","Aidez-moi à résoudre le problème...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, je vous attendais, patron. Jan Svenson a averti que vous viendriez sûrement voir comment les choses se passent à Le Francois. J'ai pris tout en main et je jure par la foudre, ce village vivra mieux qu'avec ce maudit Kindman, que les diables s'amusent avec lui dans les plus sombres caves de l'enfer !";
					link.l1 = "Tu es Jean David, n'est-ce pas ? Svenson a dit quelque chose à propos de ma part...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" chef. Tout va bien à Le Francois, comme toujours. Pourquoi êtes-vous venu ? Puis-je vous aider avec quelque chose ?";
					link.l1 = "Je suis juste passé pour voir comment ça va.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "Et ma part ?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+"  matelot.Pourquoi es-tu venu? Puis-je t'aider avec quelque chose?";
				link.l1 = "Je suis juste passé pour dire bonjour.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "À votre service, patron ! Quant à la part - le cinquième de chaque mois, une partie des pièces d'or provenant des exploits de nos gars vous sera déduite, et elle vous attendra autant que vous en aurez besoin. À partir du mois prochain, vous pourrez venir la récupérer.";
			link.l1 = "Chouette !";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "Et je m'occuperai du reste. Le Diable de la Forêt a dit que tu n'aurais pas le temps de t'occuper de ces petites choses comme Le Francois...";
			link.l1 = "On vous l'a bien dit. Bien, Jean, je compte sur toi, j'espère que tu ne me laisseras pas tomber.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Tout ira bien, patron. Tout est sous contrôle ici, ha-ha, et que je sois privé de rhum jusqu'à la fin des temps si je gâche quelque chose !";
			link.l1 = "Très bien, à bientôt !";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "En vous attendant, patron. Pendant ce temps, nous avons rassemblé pour vous "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+"  Prends-le.";
			link.l1 = "Ha, pas mal. Bien joué, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Je fais de mon mieux, patron. Revenez le mois prochain ou quand vous voulez - votre argent sera en sécurité avec moi.";
			link.l1 = "D'accord, à bientôt, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Resoudre le probleme ? As-tu la moindre idee de ce que tu as fait ? Quoi qu'il en soit, apporte-moi un million de pesos et je persuaderai les gars d'oublier ton acte. Si l'idee ne te plait pas, alors va au diable.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Bien, je suis prêt à payer.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Compris. Je m'en vais.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bien ! Considérez-vous de nouveau propre. Mais j'espère que vous ne ferez plus de telles choses dégoûtantes.";
			link.l1 = "Je ne le ferai pas. Bien trop cher pour moi. Adieu...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
