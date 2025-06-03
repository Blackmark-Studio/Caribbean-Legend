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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Bienvenue dans ma demeure ! Je m'appelle Christian. Christian Deluce. Que puis-je faire pour vous ?";
			link.l1 = "Je suis le capitaine "+GetFullName(pchar)+". Je cherche à acquérir une cargaison d'alcool. Vous voyez de quoi je parle ?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Quoi ??? Qui vous a dit cela ? C'est une erreur, je vous assure, je ne fais aucun commerce d’alcool !";
			link.l1 = "Ah-ha. Je vois que je suis au bon endroit.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Oh non-non, pas du tout ! Du commerce d’alcool, moi ? Je... je fais juste, euh, disons... Oui, j’ai des marchandises, mais tout est légal ! J’achète simplement pour des particuliers, euh... pour des fêtes, de petites réunions.";
			link.l1 = "Pourquoi tant d’inquiétude ? Je ne suis pas venu"+GetSexPhrase(" pour vous arrêter","e pour vous arrêter")+", mais pour contribuer à la prospérité de votre affaire. Et j’espère que mes poches se rempliront de quelques doublons.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Moi ? Inquiet ? Mais pas du tout ! Pourquoi le serais-je ? Je suis un citoyen honnête, ma maison est juste à côté de la résidence du gouverneur. Je ne viole aucune loi, je vous l’assure !";
			link.l1 = "Donc, vous ne vendez pas d’alcool ? Dommage, vraiment dommage. Voyez-vous, j’ai une proposition très avantageuse. Je suis sûr qu’un petit marchand clandestin n’en a jamais rêvé. Mais si vous n’êtes pas la personne que je cherche, alors je vais partir. N’est-ce pas ?";
			link.l1.go = "Kristian_5";
		break;

		case "Kristian_5":
			dialog.text = "Ah... attendez... "+GetAddress_Form(NPChar)+"... pardon, j’étais tellement nerveux que j’ai oublié votre nom.";
			link.l1 = "Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", en vérité, eh bien... je sais où trouver celui que vous cherchez. Je pourrais lui transmettre... votre proposition.";
			link.l1 = "Transmettre ? Vous pensez vraiment qu’une affaire aussi délicate devrait passer par des tiers ?";
			link.l1.go = "Kristian_7";
		break;
		
		case "Kristian_7":
			dialog.text = "Vous avez raison. Mais... eh bien... advienne que pourra... oui, je suis bien celui que vous cherchez.";
			link.l1 = "Voilà qui est mieux, Christian. Voyez-vous, la taverne souffre actuellement d'une grave pénurie d'alcool, et j'espère que nous pourrons en tirer parti tous les deux.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Capitaine, je suis bien au courant des difficultés de l’aubergiste. Tout le monde vient me voir, et cela commence à m’effrayer. Trop d’yeux nous observent désormais. J’espérais que vous... eh bien, vous comprenez...";
			link.l1 = "Pourquoi ne pas lui avoir proposé vos services ?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "Lui... il ne ferait jamais affaire avec moi. Cet homme méprise les petits commerçants comme moi.";
			link.l1 = "Oui, j’en ai entendu parler. Avec vous peut-être pas. Mais avec moi – sûrement.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Vous voulez servir d’intermédiaire ? Eh bien, je n’y vois pas d’inconvénient... nous avons reçu une cargaison récemment – un record ! Elle aurait pu me suffire pendant six mois. Mais, Dieu m’est témoin, seul un miracle nous a sauvés de la découverte.\nJe ne comprends toujours pas comment nous avons échappé au filet du gouverneur. Répéter cela une seconde fois serait un suicide.";
			link.l1 = "Dans ce cas, il est peut-être temps de sortir de l’ombre. En partie, du moins.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "S-sortir de l’ombre ? Mais... cela demande des contacts ! Et de l’argent ! Et pour quoi faire ? Vous, capitaine d’un navire, comptez rester en ville pour gérer les livraisons d’alcool d’une auberge ?";
			link.l1 = "Pour les contacts, je pense pouvoir vous aider. Quant à l’argent... je doute que cela demande une fortune. Et pour ce qui est de la gestion, cela ne sera pas nécessaire. Vous agirez en mon nom. Je vous aiderai, et vous m’aiderez en retour, régulièrement. Vous aurez un débouché stable, et moi, un fournisseur fiable. Cela vous convient-il ?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Je croyais que c’était un piège. Mais, franchement, votre proposition semble... très séduisante. Stabilité, fiabilité... Qui aurait cru qu’une telle chance me sourirait. "+GetSexPhrase("Monsieur","Mademoiselle")+", j’accepte ! Quelle quantité souhaitez-vous acheter ?";
			link.l1 = "Commençons par régulariser votre activité, ensuite nous discuterons des détails. Combien de bouteilles de rhum et de vin avez-vous actuellement ?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "Actuellement ? Eh bien... Allons à la cave, je pourrai vous donner les chiffres exacts.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// descente à la cave
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Voyons voir... Qu'avons-nous ici ? Ah oui\nActuellement, j'ai exactement cent bouteilles de rhum et cent bouteilles de vin.";
			link.l1 = "Eh bien, je pense que ce sera suffisant pour commencer. Si on résout le problème d'importation, pourriez-vous livrer de telles quantités chaque mois sans interruption ?";
			link.l1.go = "Kristian_16";
		break;
		
		case "Kristian_16":
			dialog.text = "Bien sûr, capitaine ! Et même trois, non, quatre fois plus si besoin ! Aucune défaillance, je garderai toujours les quantités nécessaires en réserve pour pallier tout imprévu.";
			link.l1 = "Combien souhaitez-vous pour ce lot ?";
			link.l1.go = "Kristian_17";
		break;
		
		case "Kristian_17":
			dialog.text = "Je demanderais dix doublons pour chaque dizaine de bouteilles de vin, et trois doublons pour dix bouteilles de rhum. Ce qui fait au total cent trente doublons pour toute la cargaison.";
			link.l1 = "Très bien. Je vais parler au tavernier et je reviendrai bientôt.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Capitaine, des nouvelles ? Qu’a dit le tavernier ?";
			link.l1 = "Je suis justement en route pour le voir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;
		
		case "Kristian_21":
			dialog.text = "Alors, comment cela s'est-il passé, capitaine ? Avez-vous réussi à conclure un accord avec le tavernier ?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "J'ai fait du bon travail, Christian. Il achètera ce lot et tous les suivants pour deux cent quarante doublons. Je vous paierai les cent trente doublons convenus pour ce lot, et je garderai la différence comme récompense. Tous les bénéfices futurs seront pour vous.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "J’ai bien travaillé, Christian. Il achètera ce lot et tous les suivants pour deux cents doublons. Je vous verserai les cent trente convenus pour le premier, et je garderai le reste comme récompense. Tous les profits à venir vous reviendront entièrement.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_22":
			dialog.text = "Quelle nouvelle, capitaine ! Jamais je n’aurais rêvé d’un tel marché, merci ! Mais... vous n’avez pas agi un peu vite ? Le gouverneur... je veux dire...";
			link.l1 = "Tout est réglé avec le gouverneur. Dorénavant, vous paierez cent doublons par mois en taxes et fournirez des rapports sur vos activités commerciales.";
			link.l1.go = "Kristian_23";
		break;
		
		case "Kristian_23":
			dialog.text = "Incroyable ! Comment avez-vous réussi, capitaine ? Le gouverneur est réputé strict, et farouchement opposé au commerce clandestin...";
			link.l1 = "Justement, Christian. Il est contre le commerce de contrebande, pas contre le commerce honnête. Il m’a écouté avec attention et a exposé les conditions légales. Vous opérerez en mon nom, et je serai responsable de vos actes. Ne me décevez pas, ou je vous retrouverai même dans l'au-delà.";
			link.l1.go = "Kristian_24";
		break;
		
		case "Kristian_24":
			dialog.text = "Je le jure, capitaine, vous ne le regretterez pas !";
			link.l1 = "Il ne reste plus qu’à conclure la transaction avec le tavernier, ensuite nous parlerons des détails de notre collaboration.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Bien sûr, capitaine. Êtes-vous prêt"+GetSexPhrase("","e")+" à prendre la cargaison dès maintenant ? Le prix est de cent trente doublons.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Oui, voici votre paiement.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Je n'ai pas la somme sur moi pour l'instant. Attendez-moi ici, je trouverai l'argent et reviendrai.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_25_1":
			dialog.text = "Capitaine ! Êtes-vous revenu"+GetSexPhrase("","e")+" chercher la cargaison ? Cela coûte cent trente doublons.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Tout à fait ! Voici votre argent.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Hélas, je n’ai toujours pas la somme requise. Je repasserai plus tard.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_26":
			dialog.text = "Merci ! Prenez-les ! Cent bouteilles de vin et cent de rhum, comme convenu.";
			link.l1 = "Mes matelots s’en chargeront. Moi, je vais parler au tavernier.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+" ! Vous êtes déjà là ! Alors, tout s’est bien passé ?";
			link.l1 = "Tout est en ordre, Christian. Le tavernier viendra chercher les mêmes cargaisons deux fois par mois. Assurez des livraisons régulières – et vous oublierez ce qu’est la pauvreté.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_32":
			dialog.text = "Capitaine... vous... c’est comme si le destin vous avait envoyé à moi ! C’est un véritable miracle, je n’en reviens toujours pas ! Qu’ai-je fait pour mériter autant de bonté ? Je ne sais comment vous remercier !";
			link.l1 = "Mais moi je sais, Christian. Chaque mois, vous devez réserver une partie de votre marchandise exclusivement pour moi. Je l’achèterai au prix que vous avez mentionné – dix doublons pour dix bouteilles de vin et trois doublons pour dix de rhum.";
			link.l1.go = "Kristian_33";
		break;
		
		case "Kristian_33":
			dialog.text = "Ce serait un honneur pour moi, "+pchar.name+", de vous réserver la marchandise ! Soyez sûr que je ne vous décevrai pas ! Quelle quantité souhaitez-vous ? Cinquante ? Cent bouteilles ? Dites un chiffre !";
			link.l1 = "Je n’ai pas besoin d’autant pour l’instant. Vingt bouteilles de chaque suffiront. Si j’ai besoin de plus – je vous le ferai savoir.";
			link.l1.go = "Kristian_34";
		break;
		
		case "Kristian_34":
			dialog.text = "Bien sûr, bien sûr ! Donc, vingt bouteilles de vin et vingt de rhum pour 26 doublons. Chaque mois, le 15, la marchandise vous attendra. Revenez quand vous voulez, même juste pour me saluer !";
			link.l1 = "Parfait ! Et encore une chose, Christian. J’ai mis mon nom en jeu pour vous. Ne me décevez pas.";
			link.l1.go = "Kristian_35";
		break;
		
		case "Kristian_35":
			dialog.text = "Moi... oh, capitaine... non-non, je ne vous décevrai pas ! Tout sera impeccable, je vous le jure !";
			link.l1 = "Alors, à la prochaine !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Canaille"+GetSexPhrase(""," !")+ " On ne t’a donc jamais appris que se mêler des affaires des autres, c’est chercher les ennuis ?";
			link.l1 = "C’est toi qui m’as attaqué, et maintenant tu oses dire que je me mêle de ce qui ne me regarde pas ? Tu as perdu la tête ?";
			link.l1.go = "Pirate_2";
		break;
		
		case "Pirate_2":
			dialog.text = "Par le tonnerre de Brest ! Alors toi, espèce de "+GetSexPhrase("bâtard","garce")+ ", tu ne comprends même pas dans quoi tu t’es embarqué"+GetSexPhrase("","e")+" ? Tu croyais que les ruptures d’approvisionnement de la taverne étaient dues au hasard ?";
			link.l1 = "Tu veux dire que c’est toi qui as incendié cette distillerie ?";
			link.l1.go = "Pirate_3";
		break;
		
		case "Pirate_3":
			dialog.text = "Ha-ha, enfin la lumière te parvient, qu’un boulet me transperce ! C’est bien moi ! Il était trop bien installé dans ce commerce. Mais comme tu peux le voir, je sais toujours comment éliminer mes rivaux. Et toi, tu ne feras pas exception – qu’un grappin t’emporte !";
			link.l1 = "Amusant. Voyons voir de quoi tu es capable – que les requins se régalent de ta carcasse ! Ha-ha !";
			link.l1.go = "Pirate_4";
		break;

		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Bonjour, "+pchar.name+" ! Qu'est-ce qui vous amène ?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Bonjour, Christian. Ma commande est-elle prête ?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Bonjour, Christian. Je voulais juste voir comment vous alliez. Je vais déjà repartir.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;
		
		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Bien sûr, capitaine ! Auriez-vous pu douter de ma fiabilité ?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Bien sûr que non, Christian. Voici vos doublons, je prends la marchandise.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Pas du tout. Mais j’ai oublié d’apporter les doublons. Je repasserai un peu plus tard.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Bien sûr, capitaine ! Auriez-vous pu douter de ma fiabilité ?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Bien sûr que non, Christian. Voici vos doublons, je prends la marchandise.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Pas du tout. Mais j’ai oublié d’apporter les doublons. Je repasserai un peu plus tard.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, je souhaite augmenter la commande. Disons cent bouteilles de rhum et de vin par mois.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, je voudrais discuter de l’augmentation des livraisons.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Parfait. Comme toujours, une nouvelle cargaison vous attendra le quinzième du mois. Passez donc.";
			link.l1 = "Je n’y manquerai pas. À bientôt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";

			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}

			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Capitaine, augmenter le volume est certes agréable, mais cela engendre aussi des coûts ! Plus de marchandises signifie plus de main-d'œuvre, un entrepôt plus grand, et il faudra affréter un navire plus grand... Sans investissements, je ne pourrai pas garantir les livraisons à temps.";
			link.l1 = "Et de quel montant parle-t-on ? Que faut-il pour que tout fonctionne correctement ?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Cinquante mille pesos. Je prendrai les autres dépenses à ma charge.";
			link.l1 = "Cinquante mille ? Hm... c’est une somme. N’y a-t-il aucun moyen de réduire les frais ?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Hélas, capitaine, ce n’est pas possible d’économiser ici. Si les choses ne sont pas faites comme il faut, tout pourrait... disons, très mal tourner. Et ni vous ni moi ne souhaitons cela, j’en suis certain.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Voici votre argent. Ne me décevez pas, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Christian, peut-être que ce n’est pas une si bonne idée pour le moment. Parlons-en une autre fois.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Comme vous voulez, capitaine. Si vous changez d’avis, faites-le moi savoir.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Capitaine, quelle excellente nouvelle ! Êtes-vous prêt à verser les cinquante mille pesos dès maintenant ?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Voici votre argent. Ne me décevez pas, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Je n’ai pas encore la somme requise. Je reviendrai dès que j’aurai les fonds nécessaires.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Je vous le promets, "+pchar.name+", vous ne le regretterez pas ! Je vais commencer les préparatifs immédiatement. Dès la prochaine livraison, vous recevrez cent bouteilles de rhum et autant de bon vin, pour cent trente doublons la cargaison complète.";
			link.l1 = "Très bien. Et souvenez-vous de faire preuve de prudence. Votre travail reflète aussi ma réputation.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}