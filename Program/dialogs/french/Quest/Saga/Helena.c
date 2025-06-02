// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Qu'est-ce que c'est ?";
			link.l1 = "Non, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Merci pour ton aide, capitaine !";
			link.l1 = "Mon Dieu... Tu es encore plus belle que je ne l'avais imaginé !";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Au diable avec ma beauté ! Sais-tu combien de chagrin elle m'a causé ? Je me couperais le nez moi-même si cela ne détruisait pas ma réputation. Ce salaud ne voulait pas me laisser quitter la corvette vivante, disant sans cesse que j'en 'savais trop'. Puis hier, il m'a dit qu'il en avait assez d'attendre et qu'il allait me prendre contre ma volonté. \nTu n'aurais pas pu arriver à un meilleur moment ! Mais où sont mes manières, je m'appelle Hélène McArthur. Mon papa m'appelait Rumba parce que je ne cessais de casser par accident la porcelaine fine qu'il avait 'acquise', alors c'est ainsi que mon équipage m'appelle maintenant.";
			link.l1 = "Mon nom est "+GetFullName(pchar)+" et je suis ici pour vous sauver. J'ai fouillé les Caraïbes pendant plusieurs jours à votre recherche pour le compte de Mlle Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Ms. Gladys !? Comment va-t-elle ?";
			link.l1 = "Je suis morte d'inquiétude pour vous. Mais vous la verrez bientôt, nous naviguons vers Blueweld. Vous pouvez me raconter tout ce qui vous est arrivé en chemin.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Pour être honnête, "+pchar.name+",   j'aimerais maintenant prendre un peu de nourriture et faire une sieste. Je suis épuisée après tous ces jours passés sur le navire de ce monstre...";
			link.l1 = "Bien sûr, Mlle McArthur. Je vais ordonner à l'intendant de vous servir un repas et de préparer un lit pour vous dans vos quartiers privés.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Capitaine de Maure, je vous remercie encore du fond du coeur pour votre sauvetage opportun. Vous devez venir me voir ainsi que ma mère. Notre maison n'est pas loin d'ici, sur votre gauche en venant du quai. Et sachez ceci "+pchar.name+", je ne te pardonnerai jamais si tu t'en vas sans dire adieu !";
			link.l1 = "Tout le plaisir était pour moi, Mlle McArthur. Je m'assurerai de vous rendre visite !";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, vous voilà, Capitaine de Maure ! Je suis si heureuse que vous soyez là, j'ai beaucoup de questions à vous poser.";
			link.l1 = "Je suis désolé, Mlle McArthur, mais nous devons reporter notre conversation un peu. Il me faut obtenir plus d'informations avant de pouvoir fournir des réponses satisfaisantes. Pour l'instant, je vous demande de ne pas vous montrer dans la rue. J'espère que votre attente ne sera pas longue. Faites-moi confiance et attendez.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Tu l'as dit toi-même que tu ne me pardonnerais pas si je ne passais pas.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, te voilà, mon capitaine ! Tes yeux me disent que tu as des nouvelles pour moi !";
			link.l1 = "Le capitaine Svenson m'a dit que vous vouliez naviguer avec moi. J'apprécie votre désir, et Mlle Gladys a également mentionné que la mer vous a manqué. Bienvenue à bord, Mlle Helen McArthur !";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Le capitaine Svenson m'a dit que vous voulez naviguer avec moi. J'apprécie votre souhait, de plus Mme Gladys a mentionné que vous avez manqué la mer. Bienvenue dans mon équipage, Mme Helen Sharp !";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Oui, capitaine ! Je déteste avoir à dire cela, monsieur, mais je peux me défendre et je ne tolérerai pas que les hommes prennent des libertés. Je ne suis pas responsable des mains coupées ou des yeux crevés.";
			link.l1 = "Ne t'inquiète pas, j'ai une discipline inébranlable sur mon navire. Je dois toutefois te demander quelque chose...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Oui?";
			link.l1 = "Jan Svenson et moi avons découvert que vous êtes l'héritière légitime d'Isla Tesoro. Oui, c'est vrai, ne secouez pas la tête ! J'ai la moitié de la carte qui prouve vos droits. Ce ne sera pas facile, mais Jan et moi ferons de notre mieux pour vous aider à devenir la propriétaire légitime.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = "Bonjour, mon capitaine."+pchar.name+", es-tu sérieux? Ce n'est pas gentil de taquiner une pauvre fille comme ça! Comment puis-je avoir le droit de possession d'une île entière?!";
			link.l1 = "Je suis absolument sérieux, Mlle McArthur. Et je vais vous aider à obtenir votre droit de naissance. Levons l'ancre maintenant !";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Q-que dis-tu ? Helen Sharp ? Pourquoi Sharp ?";
			link.l1 = "Helen, tu es la fille de Beatrice Sharp et l'unique héritière de la dynastie Sharp. Voici la moitié de la carte que Mme Gladys a gardée toutes ces années. C'est la preuve de tes droits sur Isla Tesoro. Ce ne sera pas facile, mais Jan Svenson et moi ferons de notre mieux pour t'aider à hériter de l'île de ton grand-père.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... Ma pauvre mère ! J'aimerais tant pouvoir trouver sa tombe un jour et prier pour son âme là-bas. Mais... attends ! Impossible !";
			link.l1 = "Qu'y a-t-il, Mlle Sharp ?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "La prophétie de la gitane vient de se réaliser... Je la comprends enfin maintenant.";
			link.l1 = "Eh? Quelle prophétie ?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", vous pourriez me traiter de naive, mais je vais vous le dire quand même. Quand j'étais une jeune fille, une gitane m'a dit : 'Ton destin sera entre les mains de l'homme qui ne prendra pas la pièce de la veuve, qui rendra l'or du mort et qui nommera la mère'\nJe pensais que c'était des balivernes à l'époque, mais d'une manière ou d'une autre vous avez réussi à accomplir chaque partie de la prophétie, vous ne pourriez pas savoir cela !";
			link.l1 = "Votre destin, dites-vous... Eh bien, peut-être avez-vous raison. Je ne vous décevrai pas. Nous chercherons ensemble la tombe de votre mère. Et pour l'instant... Mlle Helen Sharp ! Préparez-vous pour le départ et ne soyez pas en retard !";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Oui-oui, capitaine !";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Capitaine "+pchar.name+" ! J'ai une idée...";
			link.l1 = "Bonjour, mon capitaine."+npchar.name+" ? Ce n'est pas sûr ici et je t'ai dit de rester sur le navire...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, il y a tellement de poudre à canon entassée dans cette vieille baignoire que si elle explose, toute l'île volera directement à la porte de Saint-Pierre ! Peu importe si tu me dis de me cacher ou non, alors écoute-moi !";
			link.l1 = "Très bien, parle vite !";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Le corvette et la frégate. Ils ne reconnaissent pas le navire de Knive comme hostile. Nous pouvons utiliser leur complaisance contre eux. Prenons quelques barils de poudre à canon, mettons une mèche et naviguons vers les navires\nIls nous laissent approcher, nous allumons la mèche, lâchons le baril sur l'un d'eux et partons aussi vite que possible. Et ensuite, nous regarderons une explosion spectaculaire... Qu'en dis-tu ?";
			link.l1 = "Un brûlot improvisé... très rusé ! Ton plan est assez fou pour fonctionner... si nous pouvons nous approcher suffisamment sans être reconnus.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Qu'avons-nous à perdre "+pchar.name+"Ce ne sera pas facile de combattre deux navires à la fois, mais nous aurons une chance de rééquilibrer les forces...";
			link.l1 = "Très bien. Allons-y ! Les gars ! Prenez trois barils de poudre à canon ! Nous allons nous tirer d'ici ! J'adore ton imagination, "+npchar.name+"Je n'aurais jamais eu cette idée moi-même.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Oui capitaine, quel est le problème ?";
			link.l1 = "Le navire de Jackman est dans la crique de Sabo-Matila, la lourde frégate 'Centurion'. Ce navire appartenait autrefois aux Hawkes, donc il doit y avoir des objets importants et des documents dans la cabine de Jackman...nous devons l'aborder.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Plus facile à dire qu'à faire. Comment comptes-tu faire cela avec notre polacre ? Ils ont plus d'hommes et plus de canons que nous.";
			link.l1 = "Tu as raison. Jackman a au moins deux fois plus d'hommes que nous et tous sont des escrimeurs expérimentés. Ce serait de la folie de les attaquer sans un bombardement préalable. Mais un combat prolongé n'est pas non plus la meilleure option. J'ai donc réfléchi à ce qu'il faut faire.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "Bonjour, mon capitaine."+pchar.name+", ils ne nous ont pas encore reconnus comme ennemis, tout comme ces idiots de Turks... Nous pouvons essayer notre ruse à nouveau...";
			link.l1 = "Helen, je viens de te dire que nous devons monter à bord et fouiller la frégate, la faire sauter en morceaux n'est pas une option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Attends une minute, "+pchar.name+", nous ne la coulerons pas. Changeons un peu les plans. Écoute, nous allons prendre quelques tonneaux de rhum vides et les remplir de poudre à canon, de mitraille et de mèches courtes. Puis nous naviguerons plus près de leur frégate et lancerons les explosifs improvisés sur leur pont.";
			link.l1 = "Ha ! Ton ingéniosité féminine continue de m'émerveiller ! Au lieu d'un brûlot, tu proposes une fougasse ? Tu crois que ça pourrait marcher ?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Et pourquoi pas ? Leur franc-bord est plus haut que le nôtre, mais deux ou trois hommes aidés par une poulie pourraient facilement hisser et lancer un tonneau bien chargé. On criera - 'Voilà du rhum gratuit de Knive !' Et les tonneaux exploseront avant qu'ils ne puissent même réagir.";
			link.l1 = "Les mitrailles explosantes transformeront ses meilleurs hommes sur le pont en chair à pâté... Nom d'un chien, c'est tentant.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Lançons cinq barils d'un coup du gaillard arrière à la dunette. "+pchar.name+", nous avons l'élément de surprise. Ils ne soupçonneront encore rien ! Et puis, nous nous éloignerons immédiatement d'eux avant qu'ils n'aient l'occasion de monter à bord.";
			link.l1 = "Eh bien, essayons. Ils ne doivent pas nous identifier avant que nous mettions ces barils explosifs sur leur pont... Ce ne sera pas facile de s'approcher. Jackman n'est pas aussi grand imbécile que Ghoul l'était.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Risquons-le, "+pchar.name+"Comme je l'ai dit avant, qu'avons-nous à perdre ?";
			link.l1 = "Bon point... Tenez-vous prêts, les gars ! Préparez les fougasses et préparez-vous à combattre !";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Eh bien, mon cher capitaine... Il est temps pour nous de nous dire adieu. Mon service est terminé et il est temps de m'habituer à être la Reine Pirate d'Isla Tesoro. J'espère être une digne successeuse de mon oncle. Merci pour votre aide.";
				link.l1 = "Oui, c'est dommage de te quitter, mais tels sont les caprices du destin. Tu as maintenant des responsabilités bien plus importantes que de servir sur mon navire.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "J'aimerais pouvoir rester sur ton navire. Près de toi... Mais c'est impossible. Sois heureux, Charles. Et elle a intérêt à être digne de toi !";
					link.l1 = "Je suis désolé, Hélène.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "C'est si étrange, "+pchar.name+"! Je viens de devenir propriétaire de toute une île, mais je ne me sens pas reine de l'Isla Tesoro... Je suppose qu'un nouveau chef de la Confrérie gérera la colonie mieux que moi. J'ai beaucoup à apprendre.";
					link.l1 = "Ne t'inquiète pas pour ça, Helen, tu es une femme qui sait prendre soin d'elle-même - comme tu me l'as dit quand tu es montée à bord pour la première fois.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Eh bien, nous serons toujours amis, n'est-ce pas ?";
			link.l1 = "Bien sûr... Hélen, nous nous reverrons sur Isla Tesoro. Dois-je te conduire sur ton île ?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Tu as raison... Écoute, j'ai mis de côté ma part de butin en naviguant sur ton navire. Prends-la et n'essaie même pas de refuser mon offre - je ne veux pas être en dette envers toi.";
			link.l1 = "Eh bien, attends un moment...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Je sais ce que tu vas dire. Bien sûr, ton aide a été bien plus précieuse que ce maigre coffre de trésors. Mais c'est tout ce que j'ai en ma possession en ce moment et je dois te rembourser. Prends-le, si tu ne le prends pas toi-même, je le laisserai dans ta cabine.";
			link.l1 = "Allez-vous naviguer seul maintenant ? Peut-être pourrais-je vous emmener à Isla Tesoro ?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pas besoin de cela, "+pchar.name+"« Je me rendrai moi-même sur l'île. J'ai mon épée et mon pistolet sur moi, cela suffira pour un moment... Je suis sûr que la Reine d'Isla Tesoro n'a pas à s'inquiéter des revenus une fois que j'y serai arrivé. »";
			link.l1 = "Oui, oui, votre majesté. Je vous souhaite bonne chance dans votre nouvelle vie.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Assez de cela, même pour plaisanter. Je suis toujours Hélène pour toi. Mais ce n'est pas tout ce que je voulais dire. J'ai retrouvé mon père, bien que ce fut un peu étrange. Il a payé de sa bonne réputation de noble anglais pour mon héritage et cela me dérange. Le Commonwealth anglais le traque et je ne veux pas que toi, "+pchar.name+", y participer.";
			link.l1 = "Reprends tes esprits, Helen ! C'est un bandit et un pirate !";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirate ? Et qui diable es-tu pour dire une chose pareille ? Il est mon père et c'est ce qui compte pour moi ! Et moi, la fille d'un bandit et d'un pirate, je me fiche éperdument de ce que pense la justice anglaise de lui. Si tu essaies de nuire à mon père d'une quelconque manière, j'oublierai tout le bien que tu m'as fait, sache-le. Considère cela comme un avertissement.";
			link.l1 = "Vraiment ? En fait, ma fille, tu ferais mieux d'être plus polie. Je n'ai pas remarqué de plaintes de ta part concernant mon attitude de pirate lorsque je sauvais ta jolie peau des griffes de ce violeur Donovan, ou lorsque nous partagions les profits de nos captures !";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Je... je suis désolée. Je retire ce que j'ai dit, pardonne-moi. J'ai perdu la tête... Mais malgré tout, j'aimerais rester ton amie, ce qui serait impossible si tu commences à poursuivre mon père.";
			link.l1 = "Compris. Mais ne t'avise jamais de me menacer, femme. Tu devrais savoir en naviguant sur mon navire, que je ne crains ni personne ni rien. Je ne tolérerai surtout pas le manque de respect d'une femme - Reine des Pirates ou non. Je suis peut-être un gentilhomme, mais même ma patience a ses limites. Maintenant que c'est réglé, adieu. Je te souhaite bonne chance.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Merci.... Peut-être que nous nous reverrons, "+pchar.name+"...";
			link.l1 = "Et pourquoi pas ? Je visiterai Isla Tesoro plus d'une fois à l'avenir. À bientôt là-bas... Adieu, Hélène.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Je suis sûre. "+pchar.name+", je voudrais rester sur votre navire si vous me le permettez. Rester avec vous...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Tu ne comprends pas, Helen. Tout ton avenir est devant toi et tu n'as pas à t'inquiéter. Tout ce qui m'attend, c'est la guerre, les intrigues politiques et une totale incertitude. Tu dois organiser ta propre vie, il n'y a pas de place pour un vagabond sauvage comme moi dedans.";
				link.l1.go = "result_10";
				link.l2 = " (choisir Helen) C'est plus que je n'aurais pu espérer, Helen. Bien sûr, je ne veux pas te perdre, mais il vaudrait mieux que tu ailles à Isla Tesoro. Qui sait où le destin me mènera encore. Pour l'instant, j'ai une guerre, des intrigues politiques et de l'incertitude devant moi.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "C'est plus que je ne pouvais espérer, Hélène. Bien sûr, je ne veux pas te perdre, mais il vaudrait mieux que tu ailles à Isla Tesoro. Qui sait où mon destin me mènera encore. En ce moment, j'ai une guerre, des intrigues politiques et de l'incertitude devant moi.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Ne me mens pas. Tu ne veux tout simplement pas... Dis-moi, qui est-elle ? C'est cette traînée rousse de la Cité des Navires Abandonnés, n'est-ce pas ?";
			link.l1 = "Hélène ! J'essaie de te dire ce que je pense être le mieux pour toi ! Comment ne comprends-tu pas cela ?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Ah bien sûr, évidemment... Et comment a-t-elle pu te charmer, hein ? Qu'est-ce qu'elle a que moi je n'ai pas ?! Est-elle vraiment si douée ? Eh, "+pchar.name+"... Eh bien, c'est ta décision, je n'ai plus qu'à retourner sur mon île. Je ne peux pas me mettre entre vous deux\nMerci pour tout ce que tu as fait pour moi, Charles. Tu es le meilleur homme que j'ai jamais rencontré. J'espère que nous pourrons rester amis ?";
			link.l1 = "Bien sûr... Hélène, je te reverrai sur Isla Tesoro. Veux-tu que je t'y emmène ?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Pas besoin. J'achèterai un nouveau navire. J'ai amassé assez d'argent pour acheter et équiper une goélette en servant sous votre commandement. Je naviguerai à nouveau sur un nouveau 'Rainbow'.";
			link.l1 = "Je suis heureux, Helen, que tu aies été si... économe. Mais naviguer sur une goélette ne sied guère à la Reine Pirate d'Isla Tesoro. Bientôt, tu devrais te procurer une frégate pour toi.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Peut-être, "+pchar.name+". Très bien. J'irai au chantier naval mais d'abord... embrasse-moi avant que je parte... S'il te plaît...?";
			link.l1 = "Hélène...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Mon destin est lié au tien depuis notre rencontre. Ne comprends-tu pas cela ? "+pchar.name+" ? Je te suivrai jusqu'aux confins du monde !";
			link.l1 = "Et qu'en est-il de votre père ? Laurence Beltrope ? Il est mon ennemi...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Mon père est Sean McArthur. Je l'aimais et j'ai pleuré sa mort. Il était mon seul père. Et ce pirate... Je ne veux même pas en parler.";
			link.l1 = "Helen... Ma chère Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+",   j'ai toujours voulu te dire que tu es le plus grand homme que j'aie jamais rencontré ! Tu as fait tellement pour moi que je ne pourrai jamais te rembourser. Je veux rester avec toi. Pour toujours. Je t'épouserai si tu le souhaites... Je t'aime.";
			link.l1 = "Nous serons ensemble. Je le promets !"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Promets-moi de faire quelque chose pour moi tout de suite ? Et s'il te plaît, ne ris pas !";
			link.l1 = "Je te le promets, ma chère !";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Appelle-moi par mon vrai nom. Je t'en prie !";
			link.l1 = "Je t'aime, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+"Mon cher... Embrasse-moi ! J'ai attendu ce moment trop longtemps !";
			link.l1 = "Helen, ma chère...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+" ! C'était... incroyable ! Je ne veux aller nulle part ailleurs... Restons ici jusqu'au matin. Le monde peut attendre !";
			link.l1 = "Nous attendrons, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Capitaine ! Jackman est mort... Ma famille est-elle enfin en sécurité ?";
			link.l1 = "Oui, Hélène, vous êtes tous en sécurité. Mais le 'Centurion' a été coulé, tout comme tous les documents qui pourraient nous aider à trouver la tombe de votre mère et prouver vos droits sur Isla Tesoro... Eh... Maintenant, je devrai prendre d'assaut la Tortue par moi-même...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Bonjour, mon capitaine."+pchar.name+", ne t'inquiète pas tant. Il n'y a rien que nous puissions faire à ce sujet. Ne t'inquiète pas pour moi non plus, je vivrai bien sans cette île. Merci pour tout ce que tu as fait pour moi !";
			link.l1 = "On dirait que tu vas... me quitter, n'est-ce pas ?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Oui, mon capitaine. J'ai pu rassembler assez d'argent pour acheter et équiper une goélette. Je naviguerai à nouveau sur mon 'Arc-en-ciel'. Nous nous reverrons à Blueweld... Je rentre chez moi.";
			link.l1 = "Eh bien... bonne chance, Helene !";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Eh bien, mon capitaine... Il semble que nous ayons échoué. Adieu. Je rentre chez moi. J'ai gagné assez d'argent sous votre commandement pour m'acheter un nouveau schooner. Nous nous reverrons en mer !";
			link.l1 = "Bonne chance, Helen. Je suis désolé pour tout. Adieu.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Capitaine ! Jackman est mort... Il semble donc que ma famille soit en sécurité, n'est-ce pas ?";
			link.l1 = "Oui, Helen, c'est sûr. Mais je ne suis pas heureux, j'ai perdu trop de temps et Isla Tesoro est maintenant une colonie anglaise. Tu es restée sans héritage, donc je devrai prendre d'assaut Tortuga moi-même...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", qu'est-ce que l'avocat vous a dit ?";
			link.l1 = "J'ai perdu trop de temps et Isla Tesoro est maintenant une colonie anglaise. Tu as été privé de ton héritage, donc je devrai prendre d'assaut Tortuga moi-même... Hélas, nous avons perdu.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Non, mon chéri, cela ne marchera pas.";
				link.l1 = "Eh bien, pourquoi pas?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(" "+pchar.name+", je ne me sens pas bien aujourd'hui. Ne te sens pas coupable, s'il te plaît, ce n'est pas ta faute. Ne le faisons pas aujourd'hui...",""+pchar.name+", cher, je suis tellement fatiguée ces derniers jours. Pour être honnête, je veux seulement dormir. Pardonne-moi. Faisons cela une autre fois.");
				link.l1 = RandPhraseSimple("D'accord...","C'est d'accord. Comme tu veux...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Bonjour, monami."+pchar.name+" , l'ambiance est parfaite, allons-y !",""+pchar.name+"Bien sûr, sans poser de questions! Allons-y!");
				link.l1 = RandPhraseSimple("C'est ma fille...","Tu es si ravissante, Hélène...");
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("C'était merveilleux, "+pchar.name+" !.. ","Tu étais formidable comme toujours, cher..."),RandPhraseSimple("C'était génial, Charles !","J'ai passé un moment merveilleux, cher !"),RandPhraseSimple("Jamais ennuyeux avec toi, mon capitaine !","Tu étais merveilleux, chéri !"));
			link.l1 = RandPhraseSimple("Je t'aime...","Il est toujours bon d'être avec toi, Hélène...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", tu sais que je suis toujours heureuse de... Mais ce n'est pas le bon moment maintenant - nous devons attraper ce vaurien de Thibaut avant qu'il ne s'échappe.";
				link.l1 = "Tu as raison comme toujours, Hélène...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Non, chéri, ça ne marchera pas.";
				link.l1 = "Eh bien, pourquoi pas?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", je ne me sens pas bien aujourd'hui. Ne te vexe pas, s'il te plaît. Ne le faisons pas aujourd'hui..."," "+pchar.name+", cher, j'ai été si fatiguée ces derniers jours. Pour être honnête, je veux seulement dormir. Pardonne-moi. Faisons cela une autre fois.");
				link.l1 = RandPhraseSimple("D'accord...","C'est d'accord. Comme tu veux...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", je t'aime ! Allons-y !",""+pchar.name+", aye aye capitaine ! Allons-y !");
				link.l1 = RandPhraseSimple("Tu es ma bonne fille...","Vous êtes magnifique, Hélène...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Oui, "+pchar.name+"?","Oui, mon capitaine ?","Je vous écoute, "+pchar.name+"... ");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Regarde ça, mon capitaine !";
				link.l1 = "Eh bien, quelle poigne ! Je vois que tu n'as pas perdu de temps, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Chéri, à propos de tes visites aux prostituées.";
				npchar.quest.refusesex = true;
				link.l1 = "Quoi ? Helene, tu te trompes complètement ! Je voulais juste...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, je vais visiter la cité indienne perdue de Tayasal. Je ne vais pas te mentir : ce voyage est très dangereux et encore plus - il inclut une téléportation à travers l'idole. Veux-tu... me suivre ?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, donne-moi un rapport complet sur le navire.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certaines marchandises chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Je suis arrivé selon votre ordre, capitaine.";
				Link.l2 = "Helen, je dois te donner plusieurs ordres.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Penses-tu que c'est drôle ?";
					link.l1 = "Beau navire, n'est-ce pas ? Je l'ai obtenu pour toi, Helen ! Réfléchis un peu, quel genre de gars aux Caraïbes offre à sa dame un vrai bateau, hein ?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, j'ai besoin de ton conseil.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, j'ai un ordre pour toi...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, restons dans la cabine seuls... pour quelques heures ? Qu'en penses-tu ?","Chéri, passons les prochaines heures en tête-à-tête ? Aimes-tu cette idée ?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, pourquoi ne pas louer une chambre et y rester en privé... pour les prochaines heures? Qu'en penses-tu?","Mon cher, passons les prochaines heures en tête-à-tête ? Louons une chambre... qu'en penses-tu ?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, ma chère, puis-je vous inviter à passer un bon moment à la taverne ?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, il semble que j’aie trouvé la dernière volonté de ton admirateur – Francis. Il t’a légué son héritage.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Je pense que ce sabre est maintenant à toi. Blaise est ton soi-disant oncle...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Rien pour l'instant, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, chéri, es-tu malade ou quoi? Quoi, tu t'attends à ce que je descende en bas, que je balaye la cale et que je commence à compter les rats?";
			Link.l1 = "D'accord, désolé ma chérie, c'est ma faute...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Et je veux mon propre vaisseau de ligne, avec cent canons filant à 20 nœuds. J'ai été capitaine comme toi toute ma vie. Va te trouver un foutu commissaire et embête-le avec ça.";
			link.l1 = "Oui, tu as raison, Hélène. Désolé pour ça.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Je suis tout ouïe.";
			Link.l1 = "Concernant notre politique d'abordage...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "À propos du navire que vous commandez...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Rien jusqu'à présent.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Quel est votre souhait, mon capitaine ?";
			Link.l1 = "Je ne veux pas que tu abordes quoi que ce soit. Garde-toi et tes hommes en sécurité.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Je veux que tu abordes les navires ennemis à la première occasion.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Oui, mon capitaine ?";
			Link.l1 = "Je vous serais reconnaissante de vous abstenir d'échanger de navire après l'abordage. Elle est trop précieuse pour moi.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Si jamais tu abordes quelqu'un, examine bien le navire-prix. Si elle vaut le coup, n'hésite pas à la prendre pour toi.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "D'accord, je vais y réfléchir.";
			Link.l1 = "Elle y réfléchira... D'accord, comme si je pouvais de toute façon lui donner des ordres.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Très bien, j'y réfléchirai.";
			Link.l1 = "Elle y réfléchira... Oui, comme si je pouvais de toute façon lui donner des ordres.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Bien, j'y réfléchirai.";
			Link.l1 = "Elle y réfléchira... Comme si je pouvais lui donner des ordres de toute façon.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "D'accord, je vais y réfléchir.";
			Link.l1 = "Elle y réfléchira... Oui, comme si je pouvais lui donner des ordres de toute façon.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Ordres ?";
            Link.l1 = "Restez ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Change le type de munitions pour tes armes à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisissez le type de munitions :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Aussitôt, capitaine !";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aussitôt, capitaine !";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Te voilà ! Je t'ai enfin trouvé... C'était quelque chose, mon capitaine ! Je n'ai jamais vu une telle course sur un toit et un saut d'une hauteur aussi vertigineuse ! Mon cœur était prêt à exploser ! Un jour, tu me tueras avec tes tours, cher... Oh, tu n'es pas seul... Qui est cette fille ?";
			link.l1 = "C'est Catherine Fox, la fille du Colonel Fox, le commandant du célèbre Régiment Maritime Anglais de la Marine, les 'Renards de Mer'. Nous la menons à Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Vraiment...Bienvenue à bord Mlle. Fox ! .Non non, ne tenez pas le bras du capitaine de Maure, vous pouvez très bien marcher toute seule ! Et maintenant, allons à la chaloupe - il faut quitter cet endroit."; 
			link.l1 = "Ha ! Merci Helen ! Que ferais-je sans toi ? Catherine, suis-nous !";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Enfin tu t'es réveillé, cher ! Comment te sens-tu ? Tu m'as fait une peur bleue...";
			link.l1 = "Helen, que s'est-il passé? Ma tête éclate...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quand nous sommes entrés dans la cabine du capitaine, tu étais étendu par terre, immobile. Mon cœur a failli s'arrêter de battre ! Les garçons t'ont ramassé et t'ont traîné jusqu'à notre navire - juste à temps, car les morts qui gisaient sur le pont ont commencé à se relever.\nQuel horreur ! C'est presque suffisant pour me faire trouver Dieu ! Ils étaient totalement insensibles à nos lames et à nos balles ! Nous avons rapidement coupé les cordes et essayé de nous éloigner, mais une volée de leur navire a gravement endommagé notre navire et nous avons perdu le contrôle. Puis ils ont hissé les voiles et ont disparu en un clin d'œil.\nNotre navire s'est échoué, alors nous avons dû fuir vers cette rive avant que la tempête ne puisse le détruire. Beaucoup de braves gens sont morts aujourd'hui, mais le navire a survécu à la fin... si seulement je n'avais pas ordonné de l'abandonner...";
			link.l1 = "Ce n'est pas ta faute, Helen. C'était la bonne décision. Que ferais-je sans toi ?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Je t'ai tirée dans le bateau et ensuite je t'ai amenée à terre. Tu avais l'air morte, seul ton cœur battait très faiblement. Regarde ! Mes mains tremblent encore";
			link.l1 = "Merci, mon amour. Je te suis redevable. Depuis combien de temps suis-je allongée ici ?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Pendant toute une journée. J'ai lavé et bandé tes blessures, t'ai donné des médicaments et t'ai versé un peu de rhum. Maintenant, tu dois te rétablir !";
			link.l1 = "Je ne mourrai pas cette fois, chéri. Bien que je ne me sente pas bien... blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "« Dis-moi... Était-ce le véritable 'Hollandais Volant', Charles ? Pourquoi nous ont-ils attaqués ? Et pourquoi ne nous ont-ils pas tiré dessus à l'approche, mais ont-ils essayé de nous couler immédiatement après être montés à bord ? »";
			link.l1 = "Leur capitaine avait besoin de cet amulette, dont j'avais parlé à Tuttuathapak, un chaman indien. Pourquoi ils en avaient besoin, je ne sais pas... mais dès que leur chef a obtenu l'amulette, ils se sont débarrassés de nous... Dieu Tout-Puissant, quel cauchemar abominable ! Un navire dirigé par des morts-vivants ! Impossible à croire...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "« Aye, maintenant c'était notre tour de rencontrer le 'Hollandais Volant'. Gah ! Ça me donne la chair de poule ! Au prochain port où nous nous arrêtons, je vais à l'église, allumer une bougie, et prier notre Seigneur Jésus-Christ pour notre délivrance miraculeuse. Diable, je me sens tellement reconnaissant que je vais même prier quelques saints papistes... »";
			link.l1 = "Je serai là avec toi, Helen, je n'ai pas fait de vraie confession depuis un moment... Mais d'abord, nous devons retourner à ce village. Je dois tout raconter à Tuttuathapak. Ce maudit navire nous a attaqués à cause de l'amulette ! J'espère que ce diable à la peau rouge a des idées sur pourquoi diable ces morts-vivants en avaient besoin.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "D'accord. Mais nous devons être prudents - tes blessures sont à peine guéries.";
			link.l1 = "Mais tu m'aideras à guérir plus vite, n'est-ce pas ? Je t'aime, Hélène...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Je t'aime aussi, mon chéri...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", Je vous ai déjà dit que nous partageons désormais nos destins. Votre destin est mon destin. Quand partons-nous?";
			link.l1 = "Je suis très heureuse de l'entendre. Je te dirai un peu plus tard quand nous y serons. Nous devons nous préparer.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Je suis prête, mon capitaine ! Je te suivrai jusqu'aux confins de la Terre !";
			link.l1 = "Merci, mon amour...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+" ! Heureuse de te voir ! Que fais-tu ici sur Isla Tesoro ?";
			link.l1 = "Comme toujours - les affaires. Je voulais juste passer te voir aussi. Comment ça va, Helen ?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Quel est le problème avec notre cher gouverneur, Capitaine? Quel cul allons-nous botter cette fois-ci? Espagnols, pirates, ou quelqu'un de pire?";
			link.l1 = "C'est pire, Helen, bien pire. Le gouverneur a l'intention de rendre visite à une coûteuse courtisane et je suis censé l'accompagner par curiosité. Il a promis à sa maîtresse d'amener un véritable corsaire, aventurier et vieux loup de mer. Donc, je suis bon pour des discussions ennuyeuses, du vin hors de prix et des nobles ennuyeux.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Tout le contraire, une invitation à un agréable événement social, organisé par une dame. Son Excellence m'a pris par surprise en me demandant de l'accompagner, mais pour être honnête, je suis contente de me changer les idées du travail pour une fois.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Aye...alors le redoutable capitaine Charles de Maure va s'habiller et danser comme un singe de compagnie pour leur amusement ? Comme c'est charmant ! J'ai une meilleure idée. Mettons les voiles et foutons le camp d'ici. Si tu es d'humeur pour des vacances bien méritées, cap sur Isla Tesoro. Nous y sommes toujours les bienvenus. Bain de soleil, sable blanc, vieux amis, punch au rhum, oublier nos soucis - tout ce que tu veux.";
			link.l1 = "Écoute, tout cela semble fantastique, et j'adorerais... mais plus tard. J'ai promis au gouverneur, cette affaire est importante pour le vieil homme et...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Et quoi alors ? Tu crois que ton sang noble a la moindre importance pour eux ? Je ne suis peut-être pas de sang français, mais je connais tout de leur 'haute société' et pour eux, Charles de Maure n'est pas un capitaine que les hommes suivent et en qui ils confient leur vie. Ce n'est pas un gentilhomme comme eux. Les vrais gentilshommes ne prennent pas la mer pour se battre dans un brouillard de fumée de poudre à canon. Charles de Maure est juste une curiosité à leur table. Comme un léopard domestique ou un esclave déguisé en costume ! Un jouet de luxe ! Depuis quand acceptes-tu un tel traitement ?!";
			link.l1 = "Helen, s'il te plaît, calme-toi. Je suis certain que je peux supporter quelques regards désagréables pour satisfaire le gouverneur et assurer notre prospérité future. C'est bon d'avoir des amis puissants. Après tout, cela sera plus facile que de mener une équipe d'abordage ! Et ces 'bons à rien' ne sont pas toujours comme ça. Même la haute société a des gens dignes... du moins, c'est censé être le cas.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Peu importe. (elle se passe la main dans les cheveux) Mais sois prévenu - pas question que je me glisse dans une robe de soirée. Si tu m'y obliges, je porterai mes culottes. Je me fiche bien que toutes les dames des Caraïbes s'évanouissent de désapprobation.";
			link.l1 = "Je n'allais pas te forcer. Inutile que nous souffrions tous les deux. Je vais traverser cette réception et ensuite nous voguerons vers Isla Tesoro. Pour te récompenser, j'ai gardé une caisse d'excellent madère espagnol dans la cale...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles ! Diriez-vous que je ne suis pas digne d'une si estimée compagnie ? Qu'une fille en culottes gâcherait votre soirée ? Que c'est intéressant. Très bien, mais n'oubliez pas de vous habiller comme un dandy. Les singes en robes élégantes peuvent toucher même le cœur d'une courtisane. Bonne représentation !";
			link.l1 = "Hélène, attends ! Nom de Dieu... femmes !";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Ouais, nous avons bien mérité un peu de repos. Mais maudite soit-je si je vais m'entasser dans une robe élégante pour ça. A ton avis, jusqu'où iront les ragots sur ta femme habillée comme un homme et un marin ?";
			link.l1 = "Ah...Je ne pense pas que ce soit une bonne idée. Comment dire...ce n'est pas un événement où les hommes amènent leurs épouses ou des dames respectables...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha ! Putains et dépravation ! Juste merveilleux - donc tu vas à une orgie ! Alors pourquoi diable ne l'as-tu pas dit plus tôt ? Tu as de la chance que je ne sois pas une garce jalouse et que je ne te tire pas dessus là où tu te tiens. Du moins pas pour l'instant.";
			link.l1 = "Helen, s'il te plaît, tout ce que je fais, c'est accompagner notre gouverneur, il me l'a demandé et il a été très insistant à ce sujet. Il n'y aura pas de foutues courtisanes\nAttends, ça sonne mal... Je veux dire qu'il y aura des foutues courtisanes... Oh bon sang ! Je rends juste mes respects !";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Je vous suggère de vous habiller à la mode pour 'présenter vos respects', Capitaine de Maure. C'est la haute société et tout ça. C'est un pur scandale de s'y présenter sans col et poignets. Même pour une orgie. Amusez-vous bien.";
			link.l1 = "Helen, attends ! Bon sang...femmes !";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Des manchettes et un col, Capitaine. Et peut-être de la dentelle. J'ai entendu dire que c'est à la mode de nouveau. Mais qu'est-ce que j'en sais !";
			link.l1 = "Oh Helen, allez !";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Regarde ça ! Mon cher capitaine, de retour chez lui après son orgie !";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Est-ce que la noblesse locale approuve toujours leur nouveau singe ? Eh bien, ils disent que sa prestation d'hier soir était légendaire ! Parier sur des navires et des catins, défier des jeunes princes à des duels ? Auriez-vous l'amabilité d'expliquer ce diable de comportement ?";
			link.l1 = "Helen, laisse-moi expliquer ! Ce n'est pas si simple. Bon sang, je suis désolé, mais je n'aurais jamais cru devoir passer la nuit chez Madame Botot. J'y ai seulement dormi, oui seul je le jure ! Et oui, j'ai gagné une frégate à un jeu de cartes. Imagine ça ?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Eh bien ! Vous êtes soit un grand menteur, un saint, ou un imbécile. Nous discuterons plus tard des putains et des navires que vous avez gagnés - maintenant racontez-moi tout sur le duel et pourquoi tout le monde murmure que vous avez défié un prince héritier ?";
			link.l1 = "Pas un prince héritier, seulement le bâtard d'un comte. Il est le fils d'un noble très influent, le comte de Lévi Vantadur. Écoute, je n'ai pas commencé ! C'est lui qui m'a défié en premier, et maintenant je dois gagner le duel sans trop le blesser pour éviter la colère de son père.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, 'seulement le fils d'un comte' hein? Tu es sérieux en ce moment, Charles ?! Et comment sommes-nous censés faire cela ? Et s'il triche ? Il te tuera !";
			link.l1 = "C'est pourquoi Son Excellence m'a fourni des seconds nobles. Je ne prendrai qu'eux avec moi - si les choses tournent mal, au moins je pourrai prouver que tout s'est passé selon le code du duel et la loi. Je vous demande de veiller sur la frégate pendant mon absence.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Assurons-nous que j'ai bien compris... Tu as disparu pendant toute une journée et une nuit et tu as gagné une catin et une frégate à un jeu de cartes. Et maintenant, tu es sur le point de te battre avec un noble fils de pute que tu n'as pas le droit de tuer, pendant que *je* reste ici à attendre? Comment suis-je censée me sentir à propos de tout ça?!";
			link.l1 = "Helen, écoute, tu as tous les droits d'être fâchée contre moi et je suis vraiment désolé, mais c'est juste...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Tu sais quoi, j'en ai assez de tout ça. Va faire ce que tu as à faire ! Je vais juste dépoussiérer ta cabine et laver ton linge sale ! Ne pense même pas que tu t'en tires à bon compte. Nous en parlerons quand tout cela sera terminé. Je m'occuperai de ta nouvelle frégate, grand Capitaine de Maure, ne t'inquiète pas. Oh, et Capitaine de Maure, essaie de ne pas mourir... car j'ai l'intention de te tuer moi-même ensuite. Maintenant, excuse-moi, je vais m'enfermer dans mes quartiers et boire une bouteille de ce bon madère que j'ai trouvé dans ta cabine.";
			link.l1 = "Helen, laisse-moi juste expliquer ! Merde... C'est reparti !";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "J'ai entendu dire que la dernière mode parisienne exige que les gentilshommes gagnent des navires et des courtisanes aux jeux de cartes plutôt que de les acheter ! De plus, si l'on veut faire bonne impression, il doit défier leurs anciens propriétaires en duel. Dans quel bordel t'es-tu encore fourré cette fois-ci ?!";
			link.l1 = "Helen, ce n'est pas si simple. Bon sang, je suis désolé, mais je n'aurais jamais pensé devoir passer la nuit chez Madame Botot ! La nuit dernière s'est transformée en une bataille épuisante et brutale d'esprit. Et oui, j'ai gagné une sacrée frégate aux cartes. Imagine ça ?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Charmant. Cela signifie que tu as gagné une courtisane aussi ? Et la frégate que tu as gagnée, qu'as-tu misé contre elle ? Pas notre navire, tu n'aurais pas pu...";
			link.l1 = "Je devais le faire. Ecoutez, cela n'a plus d'importance maintenant, j'ai gagné à la fin. Mon adversaire m'a défié en duel et m'a accusé de tricherie. C'est un bâtard d'un noble extrêmement influent, le comte de Levi Vantadur. Ce qui signifie que je devrai faire de mon mieux pour ne pas le tuer ou le blesser trop gravement.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Fera-t-il de même ? As-tu perdu la tête, Charles ? Risquer ton navire, risquer ta vie, pour une autre femme ?! En vaut-elle vraiment la peine ? Ne suis-je rien pour toi ?!";
			link.l1 = "Helen, il n'y a aucune raison d'être jalouse, je te le jure. Cela s'est juste passé. Je devais le faire et le gouverneur m'a fourni des officiers nobles comme mes seconds pour s'assurer que tout se passe selon les règles. Je ne peux ni t'emmener ni emmener aucun de nos hommes avec moi. S'il te plaît, prends soin de la frégate pendant mon absence.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Juste génial ! D'abord, tu vas à une orgie avec des femmes étranges et tu reviens le lendemain matin et je ne t'ai même pas corrigé pour ça. Maintenant, tu me dis que tu as presque perdu notre navire dans une partie de cartes mais gagné une courtisane ! Et maintenant, tu es sur le point de te battre pour son 'honneur' contre un fils de noble à qui tu n'as même pas le droit de régler son compte ! Comment suis-je censée me sentir face à tout ça ? Dis-moi.";
			link.l1 = "Helen, écoute, tu as tous les droits d'être en colère contre moi, mais laisse-moi juste expliquer...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Tu sais quoi, j'en ai assez de tout ça. Va te battre en duel, bon sang. Je m'occuperai de ta nouvelle frégate, grand Capitaine de Maure, ne t'inquiète pas. Maintenant, excuse-moi, je vais m'enfermer dans ma cabine et boire une bouteille de ce bon madère que j'ai trouvé dans ta cabine. Mais s'il t'arrive quelque chose, je jure devant Dieu que je ferai pleuvoir le feu de l'enfer sur cette ville et j'enterrerai ce bordel et le palais de ton bien-aimé Excellence !";
			link.l1 = "Helen, ça ira, fais-moi confiance... Attends, où vas-tu ?! Nom d'un chien ! C'est reparti...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, tu as des explications à donner. Aurais-tu l'amabilité de me dire ce qui diable s'est passé ? Je n'ai pas mis de garde appropriée et les gars buvaient... des vauriens ont attaqué notre navire et nous ont ligotés pendant que nous dormions. Ensuite, la vermine immonde a commencé à me demander jusqu'où tu irais pour me sauver. Finalement, ils m'ont enfermée dans la cale. J'ai perdu le compte des jours que j'ai passés à attendre !";
			link.l1 = "Ce salaud voulait se venger de la honte que je lui ai infligée. J'avais peur qu'il te fasse du mal ! Dieu merci, tu vas bien !";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Je suppose que tu as dû faire quelque chose pour me récupérer ? Quelque chose de mauvais, n'est-ce pas ?";
			link.l1 = "Tout ce qui compte, c'est que tu sois de retour avec moi. Je t'ai laissé tomber, Helen. Je suis tellement désolé ! J'espère que tu pourras trouver dans ton cœur le moyen de me pardonner !";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Je l'ai déjà fait. J'ai eu beaucoup de temps pour réfléchir à ce que j'ai dit...Je suis désolée aussi, Charles. Si seulement je n'avais pas pris tes affaires avec ce marquis trop à cœur. J'aurais posté une véritable vigie cette nuit-là, je serais restée sur mes gardes. Ah! Je ne suis qu'une femme inutile!";
			link.l1 = "Arrête de dire ça, le passé est le passé. Je t'aime et je ne te quitterai plus jamais. Je te le promets !";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Je suppose qu'il vaut mieux que je ne sache pas exactement ce que tu as fait, n'est-ce pas ? Très bien, nous sommes de nouveau ensemble et c'est le principal.";
			link.l1 = "Je n'ai aucun secret pour toi. Je te dirai...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Quel bazar... Je sais que tu n'avais pas le choix, mais comment expliquer cela à Di Lu Parkes et à ses amis ? Je veux dire, tu es un criminel maintenant !";
				link.l1 = "J'ai choisi de payer ce prix, mais je n'avais vraiment pas le choix. Ne t'inquiète pas, je trouverai un moyen de réparer cela et de restaurer notre bon nom. Sinon, nous serons toujours les bienvenus à Isla Tesoro ! Je peux gérer si tu es avec moi.";
			}
			else
			{
				dialog.text = "Quelle histoire Charles... Je crois que tu n'avais pas le choix, mais que se passera-t-il ensuite? Cet Anglais arrangera-t-il les choses ou est-ce la guerre? Tu es sûr que tu ne veux pas venir à Basse-Terre pour voir ce salaud enchaîné?";
				link.l1 = "Tu sais, Helen, il y a deux semaines, je n'aurais jamais raté ça. Mais aujourd'hui, je dis au diable avec lui ! Je me moque même de sa juste punition. Nous sommes ensemble à nouveau, c'est tout ce qui compte !";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Tu sais que je serai toujours avec toi. Ha ! Ce n'est pas comme si c'était la première fois que toi et moi nous retrouvions jusqu'au cou dans les cales. On s'en sortira encore.";
				link.l1 = "C'est vrai. Hissons les voiles, cher ! L'horizon nous attend !";
			}
			else
			{
				dialog.text = "J'aime ta façon de penser, Charles ! Plus de nobles : Français, Britanniques, Espagnols - peu importe. Je pense que nous avons bien mérité des vacances !";
				link.l1 = "D'accord. Juste toi et moi ! Plus de gouverneurs ni de bâtards de haute naissance !";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aye, aye, Capitaine !";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Cela semble charmant ! Je vais dire aux garçons qu'il est temps de lever l'ancre ! Et Charles...";
				link.l1 = "Je sais Helen, je sais. Je te rejoindrai dans un instant.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, tu l'as fait ! Les Portugais m'ont tout dit ! Quelle histoire !";
			link.l1 = "Dieu merci, tu es en vie, Hélène ! Tu n'as pas idée à quel point je suis heureux de te revoir !";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "En parlant de cela. Tu as promis de me dire quelque chose, tu te souviens ? Quelque chose de grand et compliqué. C'est ta chance, Capitaine. Qu'est-ce qui diable s'est passé ?!";
			link.l1 = "Je t'aime, Hélène. Le reste est sans importance.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Aye, cela a été utile, mais... Bon sang, moi aussi, Charles. Je t'aime aussi. Mon Dieu, tu m'as tellement manqué !";
			link.l1 = "Moi aussi. Viens avec moi, je ne te quitterai pas ce soir, même si le ciel commence à tomber sur cette misérable ville. Je ne te quitterai plus jamais. Jamais.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Je suppose qu'il vaut mieux que je ne sache pas exactement ce que tu as fait, n'est-ce pas ? Aye, nous sommes de nouveau ensemble et c'est l'essentiel.";
			link.l1 = "Je n'ai aucun secret pour toi. Je te dirai...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "« Incroyable ! Vient-on de dire que la France et l'Angleterre sont au bord de la guerre l'une contre l'autre à cause de moi ? »";
			link.l1 = "Non, Hélène. C'est parce que j'ai fait une très mauvaise erreur de jugement. Mais je devais te ramener et tout arranger.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "C'est très touchant et romantique, je suis même prête à oublier comment tout cela a commencé. Presque prête. Mais sérieusement, ils t'ont arrêté parce que les Portugais ont donné un mauvais nom du maudit brigantin ?";
			link.l1 = "Au contraire, il m'a donné le bon ! J'aimerais savoir comment il a réussi ce coup et pourquoi. Au fait, où est donc cet homme ?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Il est parti. Juste après m'avoir amenée ici. Je ne voulais pas profiter de 'l'hospitalité' de la courtisane que tu as gagnée, alors j'ai demandé à Bartholomew de me louer une chambre. Il l'a payée et a disparu sans dire un mot. En fait, attends, non, il t'a quand même laissé une lettre !";
			link.l1 = "Une lettre? De Bartholomew le Portugais? Voilà qui est nouveau. Je n'aime pas où cela mène...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "D'accord, je te laisse le lire ici pendant que je vais dire bonjour aux gars. Ils doivent être inquiets. Je n'aurais jamais cru que ces visages lugubres et abattus me manqueraient ! En attendant, essaie de ne pas te fourrer dans un autre désastre !";
			link.l1 = "Bon sang... Je n'arrive toujours pas à croire que je t'ai ramené !";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Sable blanc, eau verte claire, toi, moi, et du bon vin - Charles, c'est si romantique ! Nous devrions souvent nous promener ainsi ensemble, d'accord !";
			link.l1 = "Content que cela te plaise. Je pense que nous devrions prendre plus de temps pour cela maintenant.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, que fais-tu et pourquoi es-tu à genoux? C'est si soudain...";
			link.l1 = "Helen, je t'aime. Et je veux vivre avec toi chaque jour qui m'est accordé d'en haut. Par conséquent, ici et maintenant, face à cette mer et ce ciel, je te demande - Helen Beatrice Sharp - de me faire l'honneur de te tenir à mes côtés devant les hommes et Dieu jusqu'à ce que la mort nous sépare. Moi, Charles de Maure, Chevalier de Monper, te demande - veux-tu m'épouser ?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Tu sais, je n'ai jamais aimé ces formalités, mais je suis avec toi jusqu'au bout du monde. Et pour ta question, la réponse est... oh, désolée, j'ai renversé !";
				link.l1 = "Peu importe, c'est juste du vin et je n'ai jamais aimé cette chemise...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, bien sûr que oui ! Oui, oui, et encore oui !!! Mais j'espère que tu ne prévois pas de nous retirer dans quelque château familial poussiéreux pour cultiver des navets jusqu'à la fin de nos jours ?";
				link.l1 = "Eh bien, nous avons un château familial, mais il n'est pas poussiéreux et nous n'y resterons pas. Notre vie, c'est la liberté et l'horizon à portée de main !";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Alors un toast pour toi, mon capitaine, mon époux, et pour notre mariage !";
			link.l1 = "À toi, mon amour ! Et à notre avenir ensemble, tant de choses nous attendent !";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Alors un toast à toi, mon capitaine, mon mari, et à mon mariage !";
			link.l1 = "À toi, mon amour ! Et à notre avenir ensemble, tant de choses nous attendent !";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Alors, l'Abbé Benoît est revenu et est prêt à nous marier. Mais sache que je ne porterai pas de robe même pour une telle occasion ! Penses-tu que me voir en culottes provoquera un scandale ?";
			link.l1 = "Helen, je t'aime dans n'importe quelle tenue, et ils s'y habitueront. D'abord, je voulais te consulter à propos des invités et de la cérémonie.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Oui, il y a un problème - la plupart de nos meilleurs amis avec qui nous aimerions partager cette journée ne seront pas autorisés à entrer dans la ville, encore moins dans l'église. Donc - marions-nous ici avec toutes les personnes importantes, comme prévu, puis naviguons vers Isla Tessoro et faisons une vraie célébration avec nos vrais amis, qu'en penses-tu ?";
			link.l1 = "Ça me paraît bien ! Je parlerai à l'abbé Benoit, mais nous devons envoyer des invitations et plus encore...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Calmez-vous, capitaine. Votre future épouse chérie prendra une partie du fardeau ! Je vais tout organiser sur Isla Tesoro et écrire à nos amis, dites-moi simplement : de quelle taille voulez-vous le mariage ?";
			link.l1 = "Rien que toi, moi et nos amis les plus proches. Après toute cette fanfaronnade officielle ici en Martinique, nous voudrons un peu d'intimité sincère.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Tout le monde doit se souvenir de ce jour ! Appelez tout le monde ! Personne ne sera laissé de côté !";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Confortable et amical - tu as lu dans mes pensées ! Nous devrons visiter Sharptown et je préparerai tout. Je pense que cinquante barils de rhum et deux douzaines de barils de vin seront suffisants. De plus, pour la nourriture et le divertissement, nous aurons besoin de trois cent mille pièces de huit.";
			link.l1 = "Rappelle-moi - pourquoi ne gères-tu pas à nouveau les finances du navire ? Je m'occupe de tout. Juste une visite rapide chez l'abbé et ensuite nous mettons les voiles pour Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Alors, tu veux faire la fête comme de vrais loups de mer ? D'accord ! Nous devrons visiter Sharptown et je préparerai tout. Nous devrons sérieusement nous approvisionner - je pense que cent tonneaux de rhum et cinquante tonneaux de vin suffiront. Et les autres dépenses prendront au moins cinq cent mille pièces de huit.";
			link.l1 = "Invites-tu l'intégralité des Frères de la Côte ? Oh diable, faisons-le ! Je vais chercher les provisions. Juste une visite rapide chez l'abbé et nous mettons les voiles pour Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, je m'occuperai du chargement, puis je distribuerai les invitations au baron et trouverai un accord avec le tavernier. Cela ne devrait pas prendre trop de temps.";
			link.l1 = "Ne t'inquiète pas ma chère, je m'occuperai avec un travail lucratif... Ou je ferai juste une sieste sur le sable. Je ne pensais pas qu'il serait plus facile de prendre d'assaut la Tortue que de planifier mon propre mariage, pour l'amour du ciel.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "As-tu pu te reposer, Charles ? J'ai de bonnes et de mauvaises nouvelles. La mauvaise, c'est que les locaux se sont tellement amusés la semaine dernière qu'ils ont accidentellement brûlé cette satanée taverne 'Le Vieux Pivert' ! Voici la bonne nouvelle, le baron a promis qu'elle serait reconstruite, plus grande et meilleure qu'elle ne l'était, d'ici notre retour. J'ai pris les dispositions nécessaires, donc nous pouvons mettre les voiles.";
			link.l1 = "J'espère que notre mariage ne laissera pas une pile de cendres similaire en ville quand nous partirons. C'est bien dommage, j'aimais bien le 'Vieux Pivert' - douillet, intime, avec juste une légère odeur de vomi et de filasse! Enfin, ma chérie, tu as raison - nous devrions y aller.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan est déjà en ville avec Gladys, peux-tu imaginer? Je ne pensais pas qu'ils assisteraient un jour à mon mariage ! Oh doux Jésus ! Même lorsque nous étions dans cette horrible ville-temple indienne, je n'étais pas aussi effrayée que je le suis maintenant !";
			link.l1 = "Tout va bien, chéri, tout va bien. Je suis inquiète aussi - les nerfs sont normaux. Puisque les invités sont déjà arrivés, je devrais aller voir le Père Benoît et savoir quand le service commencera.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Ca va etre une fichue longue et difficile journee... Je vais voir Jan et Gladys.";
			link.l1 = "Je suis contente qu'ils aient pu venir. Le vieux Svensson t'aime comme sa propre fille, et Mme McArthur encore plus. C'est bien qu'ils soient là aujourd'hui. Va et ne t'en fais pas - tout ira bien.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Oui.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Oui.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Oui.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "Bonjour, camarade.";
			link.l1 = "Moi, Charles Henry de Maure, chevalier de Monper, te prends, Helen Beatrice Sharp, pour être mon épouse, pour t'avoir et te chérir, à partir de ce jour, pour le meilleur et pour le pire, pour la richesse et la pauvreté, dans la maladie et dans la santé, jusqu'à ce que la mort nous sépare. Selon la Sainte Loi de Dieu, en la présence de Dieu, je fais ce vœu.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Moi, Helene Beatrice Sharp, te prends, Charles Henry de Maure, pour époux, pour t'avoir et te chérir, dès ce jour, pour le meilleur et pour le pire, pour la richesse et la pauvreté, dans la maladie et la santé, jusqu'à ce que la mort nous sépare. Selon la sainte loi de Dieu, en présence de Dieu, je fais ce vœu.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - oh j'aime le son de cela, mon cher époux !";
			link.l1 = "Je n'ai rien entendu de mieux, ma femme !";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Tu sais - je pensais que cela ne changerait rien, et probablement que cela n'a pas changé - je t'aimais déjà avant et je voulais vivre avec toi pour le reste de mes jours, mais ce jour, ce service sacré... Je suis vraiment heureuse, Charles ! Heureuse comme jamais auparavant, et regarde Gladys et Jan - ils rayonnent ! Il y a tant de visages heureux autour ! D'ailleurs - il est temps pour toi de faire le tour des invités et d'accepter leurs félicitations. Reviens quand tu auras terminé, n'oublie pas - on nous attend à Sharptown.";
			link.l1 = "Je le ferai tout de suite, ma chérie. Un baiser avant de partir !";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Bonjour mari, as-tu déjà parlé aux invités ?";
			link.l1 = "Pas encore, sois patiente, femme, je reviendrai bientôt.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Oui, je n'ai jamais entendu autant de félicitations d'un coup. Et tu sais quoi - je pense que la plupart d'entre eux parlaient sincèrement !";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Oui, ces nobles sont étonnamment sincères - à admettre, je m'attendais à plus de fausseté et d'hypocrisie. Ou je suis simplement si heureuse que je ne remarque rien. Mais après tout, nos amis nous attendent à Sharptown ! Quand appareillons-nous ?";
			link.l1 = "Tout de suite. Nous volerons sur les ailes des aigles directement vers un festin amical. J'espère que ma femme, cela ne vous dérange pas de passer cette nuit dans notre cabine ?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh oui, mon mari, tu es si romantique ! Et ne te tortille pas comme ça, maintenant j'ai le droit de t'embrasser en public... Oui, nous pouvons y aller maintenant !";
			link.l1 = "Navigateur, mets le cap sur Sharptown et ne nous dérange sous aucun prétexte ! Je m'en moque si une flotte fantôme s'approche de nous !";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mon cher mari, je suis tellement heureuse ! Aujourd'hui est un jour merveilleux...";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Allez Charles. Ce menteur sera mort avant de toucher le sol !";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Je vais bien, Charles, tout va bien. Comment va Nathan ?";
			link.l1 = "Tellement de sang... Dannie, respire-t-il ? Je le vois respirer !";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Plus vite, cher, ne perds pas de temps !";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, es-tu d'accord? Quel carnage! Désolée, nous étions coincés à l'étage, il y avait une douzaine de ces salauds, alors j'ai dû m'occuper d'eux d'abord !";
			link.l1 = "C'est bien, je m'en suis occupée. Je suis contente d'avoir pu finir cette histoire avec Jacques... enfin. Il a eu ce qu'il méritait.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Très bien, ma chère, finissons ici et rentrons. Je ne peux pas m'empêcher de penser à Nathan, comment va-t-il? Il m'a protégé de cette balle !";
			link.l1 = "Tu as raison, chéri, je m'inquiète aussi. Vas-y, je te suis juste derrière.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Nous avons trouvé Marcus ! Il était dans la cale, ligoté et inconscient.";
			link.l1 = "Il est vivant ?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Ne t'inquiète pas, mon amour, le baron Tyrex vivra encore plus longtemps que nous. Il vient de se réveiller et il est déjà en pleine forme, il ne cesse de demander du rhum, son sabre et le pont - dans cet ordre.";
			link.l1 = "C'est notre vieux Marcus ! Laisse-le se reposer un peu pendant que nous finissons ici et ensuite retournons à la côte.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Je suis tellement désolée, chéri... D'abord notre fidèle ami Tichingitu, maintenant Gino... Barbazon aurait dû être tué une douzaine de fois pour tout ce qu'il a fait !";
				link.l1 = "Hélas, je ne l'ai fait qu'une seule fois. Je me sens mal aussi... Mais nous avons gagné, et il ne fera plus jamais de mal à personne.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "«Je me sens si mal pour Gino, Charles ! Quand je l'ai appris, je n'y ai pas cru ! Comment vas-tu, mon amour ?»";
					link.l1 = "Je n'arrive pas à y croire non plus... quelle fin tragique... Je n'aurais jamais imaginé que cette journée se déroulerait ainsi.";
				}
				else
				{
					dialog.text = "Je me demande si les futurs historiens écriront sur la grande bataille de la Baie du Corsaire ? Le jour où les barons des Frères de la Côte se sont affrontés en bataille ouverte - je parie que la Costa Garda espagnole essuie des larmes de gratitude ! Mais, nous avons encore gagné ! Nos amis sont vivants, et nos ennemis sont morts - un cadeau de mariage glorieux !";
					link.l1 = "Oui, quelle célébration, mais nous y sommes arrivés, mon ange. Nous l'avons fait.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Allez, Dannie nous a trouvé une maison ici en périphérie de la ville, je ne veux pas retourner au navire maintenant tant qu'il n'a pas été nettoyé. Nous allons nous asseoir et boire à ceux qui ne l'ont pas fait.";
			link.l1 = "Oui, Helen, allons-y.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Je me sens tellement mal pour Gino, Charles ! Quand je l'ai appris, je n'y ai pas cru ! Comment vas-tu ?";
				link.l1 = "Je n'arrive pas à y croire non plus... Quelle fin tragique... Je n'imaginais pas que ce jour se déroulerait ainsi.";
			}
			else
			{
				dialog.text = "As-tu vu Hawk ? Dannie m'a laissée sortir quand Gino a dit 'le danger est passé'. Je suis contente que tout soit en ordre. Nos amis sont en vie, et nos ennemis sont morts - un cadeau de mariage glorieux !";
				link.l1 = "Moi aussi, chéri. Et nous avons gagné. Barbazon est mort, les barons rassemblent ce qui reste de leurs équipages. Le combat est terminé.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, je vois que tu tiens à peine debout, mais j'ai visité la taverne et tu ne croiras pas ce que j'ai entendu du barman.";
			link.l1 = "Oui, je l'ai entendu de Jan, il y est allé aussi. Il me semble que notre cher Indien est parti sur le sentier de la guerre. Allons faire un tour à la crique de Sabo-Matila, quelques personnes l'ont vu partir dans cette direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Dieu au-dessus ! C'est l'esprit, Tichingitu ! Ouf, je me marre comme un fou ici ! Pourquoi nous autres Européens n'adoptons-nous pas une telle coutume aussi ?! Oh Charles, tu es presque endormi debout ! Allez, Dannie nous a trouvé une maison ici en périphérie - tu dois te reposer un peu.";
			link.l1 = "Conduis-moi ... Je pense que je me suis déjà endormie sur cette plage.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = " ... C'est bon.";
			link.l1 = "Bon à entendre.";
			link.l1.go = "exit";
			link.l2 = "Vraiment ?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Oui.";
			link.l1 = "C'est bon à entendre.";
			link.l1.go = "exit";
			link.l2 = "Allez, je vois bien que quelque chose te tracasse !";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Je vais parfaitement bien, laisse tomber !\nCharles, va au diable ! Je déteste les cachots, je te déteste, et je déteste cette maudite île ! Sors-moi d'ici immédiatement !\nDésolée... Je n'aime vraiment pas les cachots, ne me touche pas !";
			link.l1 = "Désolé. Nous avons tous peur de quelque chose.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Laisse-nous sortir d'ici ! Charles, fais quelque chose !";
			link.l1 = "Reprends-toi!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Mon capitaine, l'ennemi a percé la coque au deuxième pont et a débarqué un groupe d'abordage. Des batailles font rage à travers le navire, et la plupart des équipes de canon sont hors de combat ! Nous devons secourir notre équipage et Hercule ! Irez-vous, ou dois-je y aller ?";
			link.l1 = "Cette fois, j'irai moi-même, Hélène ! Prends le commandement du navire et sors-nous d'ici !";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Aye aye, mon Capitaine. Je ne te laisserai pas tomber, et toi, fais attention, s'il te plaît !";
			link.l1 = "Je sais, Hélène. Et fais attention toi aussi !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "La victoire, mon capitaine ! Le groupe de débarquement a été éliminé, l'ennemi a choisi de battre en retraite et s'est dirigé vers le sud. L'état du navire est acceptable. Équipage vivant : "+GetCrewQuantity(pchar)+" gens. Rapport terminé!";
			link.l1 = "Merci, Helen, et que...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Dehabille-toi, vainqueur, ton prix est de faire ce que tu veux de moi !";
			link.l1 = "Euh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Allons-y !";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Oh, salut, Hercule. Désolée, tu nous as surpris à un moment inopportun ! Mais bon sang, je suis ravie de te voir en vie et couvert du sang de quelqu'un d'autre - un état naturel pour toi, hein !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Eh bien, Hélène, tu es quelque chose !";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Je n'ai même pas encore commencé, mon capitaine. Allons-nous célébrer ?";
			link.l1 = "Je n'ai pas besoin d'être convaincue !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Ne regarde pas, ne regarde pas, ne regarde pas... C'est un autre monde, mon capitaine ! Ça ne peut pas être comme ça !";
			link.l1 = "Je pense que c'est notre monde désormais, ma chère. Et tu as raison, ne traînons pas...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Je crains que cette pandémie ne fasse des ravages parmi tes filles, Rodrigo. Occupe-les avec du tricot ou quelque chose!";
			link.l1 = "Cette conversation ne mène clairement nulle part. Nous avons convenu que nous irons à l'église demain. Pour prier... bien sûr.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Je suis fier de toi, mon amour !";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Eh bien, Charles...";
			link.l1 = "Qu'as-tu encore en tête, Hélène ?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Le fait que le couple le plus scandaleux des Caraïbes possède deux îles entières ! Mon refuge pirate d'Isla Tesora et ta terre promise - combien de temps penses-tu qu'ils peuvent durer lorsque la civilisation arrivera enfin aux Indes occidentales ?";
			link.l1 = "Assez longtemps pour durer toute notre vie, chéri. Et après ? Nous ne pouvons pas contrôler ce qui se passera alors. D'autres raconteront notre histoire. Le plus important, c'est que toi et moi sommes ici et maintenant, ensemble et heureux.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "En parlant de bonheur... Je vais monter là-haut maintenant : je dois allumer les bougies, faire le lit, peut-être écrire dans mon journal...";
			link.l1 = "Je resterai ici un peu plus longtemps, puis je monterai pour t'aider à 'faire le lit'.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Ne tardez pas trop...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Es-tu vraiment si occupé ? Quel dommage, mais je comprends. Je trouverai autre chose pour m'occuper.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "C'est gentil de ta part de t'en souvenir. Je voulais te dire que je suis très reconnaissante. Ce n'est pas tous les jours que quelqu'un te sauve de... tu sais quoi. Allons boire un verre. C'est moi qui régale.";
			link.l1 = "Helen... Que dira Gladys?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Très drôle, Charles. Allez, et ne m'agace pas.";
			link.l1 = "Est-ce un rendez-vous ?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "J'arrive, pas besoin de s'énerver.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha ! Tu rêves ! Il faudrait que je sois complètement ivre !";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "C'est mieux.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... elle avait de nombreuses vertus, mais elle ne tenait pas l'alcool. C'est ainsi que nous nous sommes rencontrés.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... mon père insistait sur le service militaire. J'ai cédé et je suis allé à Paris avec une lettre de recommandation. Mais je ne suis jamais arrivé à l'adresse désignée et je suis devenu artiste.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, maintenant je comprends quelles vertus tu évoques. Comment s'appelait-elle ?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Avec ces histoires, tu as complètement ruiné Paris pour moi. Je pensais que c'était une ville de grande vie, mais ça ressemble juste à un grand bordel chic.";
			link.l1 = "Condamnez-vous les bordels ?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Oui, Capitaine, et je ne comprends pas les hommes qui les fréquentent.";
			link.l1 = "(regarder dans la chope)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(avoir une toux terrible)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Euh... à chacun son goût... je suppose ?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(rit) Ha ! Tu aurais dû voir ta tête ! Effrayé ? Levons-en un autre ! À Paris !";
			link.l1 = "À Paris !";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(rit en sourdine) T-toi?! Un artiste? Alors, la beauté et la fierté de la flotte anglaise, un violeur et simple fils de pute Donovan, est mort de la main d'un artiste parisien? Ah, dommage que tu n'aies pas porté ton jabot immaculé pour l'abordage et que tu n'aies pas battu cette ordure avec une canne!";
			link.l1 = "Oui, vraiment malheureux. Le jabot se trouvait justement à la lessive ce jour-là.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(rit) Eh bien, merci, Charles. Je ne sais pas comment se déroulera le reste de la soirée, mais la nuit a déjà été formidable. Je pourrais même te permettre de peindre mon portrait. Mais, attention, pas dans le même style que celui de tes Parisiennes !";
			link.l1 = "Ha ! C'est si j'accepte de vous peindre.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "« Excusez-moi, mon capitaine, en écoutant vos aventures et la vie des nobles... courtisans des deux sexes. Que le requin me morde, je ne croirai jamais que vous n'avez pas trouvé quelque chose de plus valable à faire de votre temps ! N'osez même pas me dire que tout ce que vous avez fait, c'est barbouiller des toiles et dilapider l'argent de papa. Vous n'auriez pas survécu un jour avec nous si c'était vrai. »";
			link.l1 = "J'avais... d'autres occupations.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "Bonjour, monami.";
			link.l1 = "J'ai combiné la vie à la cour avec le service militaire, mais pas... héhé, pas tout à fait de la manière dont mon père le voulait, bien sûr. Quelques escapades par la fenêtre et une bagarre - et je suis devenu ami avec les gardes. Et naturellement, j'ai appris beaucoup de choses, renforcé mon corps. Les camarades plus âgés m'ont appris à encaisser un coup, porter une armure, manier une épée et me détendre correctement. La dernière partie m'a particulièrement convenu, bien sûr. Tu ne le croiras pas, mais tout le monde ne peut pas manier une épée du matin jusqu'à midi et ensuite boire de midi jusqu'au matin suivant.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Penses-tu que c'était facile dans la capitale pour un gentilhomme avec une mauvaise réputation et une bourse vide, perdant la lettre de recommandation de papa dès le premier jour ? J'ai dû m'affirmer et ne laisser personne se moquer de moi. Les leçons d'escrime à la maison n'ont pas été oubliées, et je répondais à tout regard de travers par un duel. Puis je m'y suis vraiment pris au jeu. Pourtant, je n'ai tué personne, et j'ai réussi à quitter Paris avant de tomber sur un combattant expérimenté qui m'aurait achevé.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "J'ai passé beaucoup de temps dans les cimetières. Ne pense pas mal - c'était juste un passe-temps populaire dans mon cercle social. Pour se donner du courage, on allait dans un cimetière la nuit, on mettait des bouteilles vides sur la grille, et on tirait dessus avec un chronomètre. Pendant la nuit, on gaspillait une centaine de balles et une caisse de champagne. Maintenant, bien sûr, j'ai honte d'un tel comportement, mais à l'époque le vainqueur remportait un gros jackpot et recevait quelques... faveurs du côté féminin de la cour. Tout était utilisé - je m'amusais même un peu avec des mélanges de poudre à canon. Mais pourquoi aucun de nous n'a pensé à apprendre à fabriquer des cartouches en papier - je ne le saurai jamais.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "J'ai étudié, et avec beaucoup de diligence - j'étais même proche d'entrer à la Sorbonne. J'ai travaillé dans un bureau jusqu'à ce que cela devienne ennuyeux, et en général - j'ai touché à un peu de tout. Le professeur, un vieil ami de mon père, préférait la pratique à la théorie, donc j'ai pu voir Paris sous tous ses angles et parler à différentes personnes : des bandits aux nobles. Tout cela s'est avéré utile ici.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "Et... c'est tout? Alors il y a encore quelque chose en toi, mon capitaine. Quelque chose que tu n'as pas encore vu en toi-même. À toi !";
			link.l1 = "Bon toast !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Raconte-moi ton histoire, Hélène. Mes aventures dans la Capitale pâlissent en comparaison à une fille de moins de trente ans commandant une goélette avec cent hommes à bord.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Juste en dessous de trente, hein, Charles ? Pour un commentaire aussi fort, tu devras payer la prochaine tournée ! Tous mes gars sont morts, et je ne commande plus de goélette. Franchement, je ne sais pas si j'en commanderai une à nouveau.";
			link.l1 = "Désolé, Hélène. Je ne voulais pas toucher un nerf sensible. Mais pourquoi penses-tu que ta carrière de capitaine est terminée ?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Mon cas, Charles, est unique. Mon père était l'un des meilleurs marins de cette région, hautement estimé par le Diable des Forêts, son équipage le vénérait, et il m'aimait plus que la vie elle-même.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Enlève ne serait-ce qu'une de ces choses, et il m'aurait soit envoyée à Londres pour vivre dans... la civilisation, soit laissée dépérir ici comme ma mère. Tout s'est bien passé au début : je voulais la liberté, la vraie liberté, Charles, et le commandement habile d'un vaisseau de guerre avec un équipage loyal te donne exactement cela. Et mon père m'a donné tout ce qu'il pouvait. Je suis partie en mer avec lui à l'âge de douze ans, j'ai passé les six premiers mois à chasser les rats dans la cale, et ce n'est qu'alors que j'ai été autorisée à travailler avec les marins.";
			link.l1 = "Sean MacArthur t'a transformée en rat de navire ? Désolé, Hélène, mais on ne revient pas de ça ! Comment l'équipage t'a-t-il acceptée ?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "Il est important pour toi. Il a clairement joué un rôle dans ton destin, tout autant que Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Oui. Tous les barons ont directement dit à mon père qu'il était un imbécile, mais c'est le Diable de la Forêt qui lui a donné son approbation et lui a serré la main après que j'ai battu le record de l'équipage en grimpant au mât. Ce moment restera avec moi pour toujours : les cris triomphants de l'équipage et, partout où je regardais, l'horizon marin dégagé. Et le regard approbateur de mon père, je ne pouvais pas le voir, mais je le sentais de tout mon cœur.";
			link.l1 = "Mon triomphe s'est terminé quand je suis tombée du gréement le premier jour en route vers la Guadeloupe.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Mon timonier, Deluc, avait aussi un regard très révélateur."}
			link.l1.go ="boire_mon_histoire_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "À nos triomphes !";
			link.l1 = "Entendez, entendez!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "À quinze ans ? Tu me fais peur, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Je n'ai même pas compris ce qui s'est passé. Le marchand hollandais avait son avant-garde - des mercenaires de la Compagnie. Ils ont décidé de faire preuve d'audace et ont contre-attaqué notre dunette. Et moi, imbécile, sans aucune crainte pour ma vie, j'ai sorti ma tête blonde. J'ai immédiatement reçu un coup de crosse de pistolet. Mais un instant avant cela, j'ai réussi à planter ma rapière dans un imbécile de la Compagnie.";
			link.l1 = "Bon Dieu, qu'en est-il de Sean ? Comment se fait-il qu'il ne vous ait pas mis à terre après ça ?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Mon père n'est pas sorti indemne de cette bataille non plus, et la vue de ma tête fêlée n'a certainement pas aidé. Il a lentement commencé à décliner, et probablement personne ne l'a remarqué sauf moi. Et puis il est parti. Selon son testament, j'ai hérité de l'Arc-en-ciel avec son équipage et suffisamment de fonds pour maintenir le navire à flot pendant un an.";
			link.l1 = "Et l'équipage t'a accepté comme capitaine ?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Nous ne vivons pas dans un conte de fées, mon capitaine. Certains ont accueilli la volonté de mon père avec hostilité - les choses ont pris une tournure désagréable\nSi au moins un marin avait quitté l'Arc-en-ciel, refusant de servir sous mon commandement, cela aurait été très mauvais pour mon image. Mais Svensson est intervenu et a remis tout le monde à sa place. Personne n'a quitté l'équipage ouvertement... à l'époque. Pendant sept ans, j'ai commandé ma beauté, transporté des marchandises douteuses pour le Diable des Forêts, cherché des trésors, vécu... Mais maintenant, tout cela appartient au passé.";
			link.l1 = "Pas dans le passé. Je crois que vous êtes destiné à naviguer à nouveau sous votre propre pavillon ! Buvons à cela !";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Nous ne récupérerons peut-être pas le navire, mais votre rapière est toujours avec vous.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Tu sais, quand tu le dis comme ça, j'y crois aussi. Buvons!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Mais est-ce que ma rapière m'apportera le bonheur ? La réponse se trouve probablement au fond de cette chope. Buvons !";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "J'ai réfléchi à ta vie en Europe... Écoute, tu es un dandy de la ville, et moi je suis juste une fille ordinaire, mais nous nous sommes déjà fait un nom dans le coin le plus dangereux du monde.";
			link.l1 = "On dirait un toast ! Alors, y a-t-il quelque chose qui nous unit ?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Eh bien, je suis sur les épaules de mon père. Je ne sais pas pour toi, mais peut-être que ta famille n'a pas eu moins d'influence sur toi ? Peut-être que tu ne t'en es pas encore rendu compte ?";
			link.l1 = "Je demanderai à mon cher frère une fois que je l'aurai sorti de prison.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Eh bien, c'est tout, mon capitaine. Nous avons échangé des histoires, il est temps de dire bonne nuit.";
			link.l1 = "Hmm, j'espérais une autre fin pour la soirée.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "La nuit n'est pas encore finie. Je propose un jeu : si tu joues bien tes cartes, peut-être que tes prières seront exaucées.";
			link.l1 = "Nous allons jouer aux cartes ? J'en suis !";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Doucement, loup de mer. Je ne jouerai pas au strip poker avec toi.";
			link.l1 = "Oui, tu as raison, Helen. Nous n'avons pas d'intimité ici.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Ce n'est pas la seule chose qui nous manque, Charles... Ce n'est pas un jeu de cartes, mais ne t'inquiète pas, je parie que tu es un maître en la matière. 'Je n'ai jamais' - tu en as entendu parler ?";
			link.l1 = "Familier. D'une vie passée. Et y joues-tu souvent ?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Toujours voulu essayer, mais personne avec qui jouer.";
			link.l1 = "C'est un jeu assez audacieux pour notre premier verre ensemble. Es-tu sûr ?";
			link.l1.go = "drinking_game_5";
			link.l2 = "D'ailleurs, où est tout le monde ? Sommes-nous seuls ici ?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Oui, apres les récents événements, j'ai besoin de vivre un peu. Faire quelque chose de fou, tu sais ?";
			link.l1 = "Non, cela finit toujours mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Commençons ! Dames d'abord !";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Renvoyez-les tous chez eux - pas besoin que des étrangers entendent.";
			link.l1 = "Non, ça finit toujours mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Allons-y ! Dames d'abord !";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Dommage, mais peut-être as-tu raison. Un autre verre alors ?";
			link.l1 = "Commençons! Les dames d'abord!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "J'ai arrangé cela - la chambre à l'étage est à vous. Elle était occupée par un officier français important, mais les gars du Diable des Forêts lui ont poliment demandé de libérer les lieux. Allez vous reposer - je ne vous laisserai pas errer dans les rues, ou pire encore, prendre la mer dans cet état.";
			link.l1 = "Oui, madame !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha ! Hic ! Cela signifie que tu commences !";
			link.l1 = "Attention, chéri ! Hmm. Je n'ai jamais chassé les rats dans la cale !";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Alors c'est comme ça ? Je dois me méfier de toi ! (Boit)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr ! Rien que le souvenir de ça... Eh bien, tiens-toi bien, beau gosse : je ne suis jamais tombée des vergues !";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Bien joué ! Permettez-moi, mademoiselle, de boire à votre santé ! (Boit)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Je n'ai jamais été superstitieuse.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "Et tu t'appelles marin ! Tu sais très bien de quel genre de personnes nous sommes. On ne sait jamais ce que le voyage apportera, on ne sait pas quand et où l'on verra terre, si jamais on la voit. Il faut chercher des réponses au-delà des cartes et des instruments de navigation ! À ta santé ! (Boit)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "Et les filles que tu as peintes en personne... Ont-elles aimé le résultat ?";
			link.l1 = "Ils n'aimaient pas toujours les peintures, mais, euh... le résultat - toujours.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles ! Si nous nous étions rencontrés à l'époque, je t'aurais tiré dessus ou pris en otage pour rançon. Et d'ailleurs, je n'ai jamais pris de pinceaux.";
			link.l1 = "Hé ! Eh bien, c'est complètement banal. Chère Hélène, si je commence à énumérer les choses que tu n'as jamais entreprises...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "D'accord, très bien, je jouerai équitablement. À toi, mon capitaine.";
			link.l1 = "(Gorgée) Hic ! Hmm...Je n'ai jamais eu mes modèles me frapper sur la tête avec la crosse d'un pistolet.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Sirote) Ugh. Nous jouons mal à ce jeu, cher. Je pensais que nous boirions et apprendrions à nous connaître, mais à la place nous échangeons des piques et... et... Hic. Nom d'un chien !";
			link.l1 = "Bonjour, mon capitaine.";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Rendons cela plus intéressant ! Et de préférence quelque chose qui ne provient pas de ce dont nous parlions il y a une heure !";
			link.l1 = "Je ne me suis jamais réveillée dans un endroit inconnu après une beuverie.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Aïe ! Bon sang, Charles ! (Boit)";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Je... Hic... n'arrive pas à y croire. Je l'avoue, coupable - le petit Rumba avait l'habitude de toucher le fond. Mais je n'ai jamais été en prison !";
			link.l1 = "Comment as-tu...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha ! Bois, bois !";
			link.l1 = "Je vais le regretter. (Boit)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "« Allez, ma chère. La dernière question et la dernière chance de me surpasser ! »";
			link.l1 = "Non... Je... Allons prendre l'air frais.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "J'ai souvent bu, mais jamais comme ça... Je ne me suis jamais soûlé à ce point avec une fille. Je le jure sur ma parole, b-boire est vraiment un g-grand péché...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "At-attendez... Vous ne buvez pas ?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha ! C'est hilarant ! Tu vises haut, mon capitaine. Que cela te soit... hic !... connu...";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "J'ai le malheur de vivre parmi un équipage entièrement masculin, et je dois me comporter avec soin. Je suis une fille honnête.";
			link.l1 = "Je suis h-heureux pour toi, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Tu seras encore plus heureux, parce que j'ai gagné ! Mais, pour être honnête, je ne me suis jamais autant enivrée avec un homme non plus.";
			link.l1 = "(Prend silencieusement un verre) À-à toi. Félicitations... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Hey-hey-hey ! Capitaine, où allez-vous ? Offensé, peut-être ?";
			link.l1 = "J'ai b-besoin... d'une pause ? Je vais juste chercher mon é-épée...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Capitaine, es-tu prêt ? Il n'y a pas de retour en arrière, et si quelque chose tourne mal, je te ferai m'épouser.";
			link.l1 = "Fiou ! Laisse-moi au moins prendre un peu l'air frais ! Es-tu sûre de cela, Hélène ?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Oui, bon sang, et ne reste pas planté là comme un piquet ! J'ai besoin de me perdre, même si ce n'est que pour une nuit !";
			link.l1 = "J'ai bien peur qu'après cette nuit, je serai celle qui voudra se perdre. Allons-y avant de réveiller toute la ville.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Attends, ma chère, pourquoi dois-je dépouiller ton patron ?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Tranchant comme un couteau, un vrai contrebandier ! Attends, je serai rapide.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Compris ?";
			link.l1 = "Tu paries ! Ce n'est pas le premier coffre que je vide, et certainement pas le dernier !";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Je suis fière de toi ! Haha ! Whiskey irlandais de première qualité, 'Bushmills' ! Ils ne nous serviront pas une telle boisson à la taverne.";
			link.l1 = "Ça semble bien, mais Svensson ne remarquera-t-il pas que ça manque ?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Il le remarquera sûrement, mais il ne le boit pas lui-même. Il semble l'avoir gardé comme cadeau pour son compagnon pirate Dodson, et Dodson a soit disparu, soit tué quelqu'un...";
			link.l1 = "C'est terrible ! Un tel don ne doit absolument pas être gaspillé. Prends le tonneau, et changeons de décor !";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Bien dit, Capitaine. Encore une chose cependant - dis-moi, as-tu pris autre chose du coffre? Réponds honnêtement.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Pris quelque chose, une habitude, tu sais.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Non. Je ne suis pas sûr d'être un pirate, mais je ne suis certainement pas un voleur.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Je te crois d'une certaine manière... imbécile que je suis !";
			link.l1 = "Bonjour, mon capitaine.";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Va t'assurer que tu n'as rien pris pour une raison quelconque.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Hé, hé, chérie ! Concentre-toi ! Mon visage, caressé par la brise marine, est juste ici !";
			link.l1 = "Ouf, eh bien, ton costume est quelque chose ! Tu as dû économiser beaucoup sur le tissu. Et moi... hic ! J'en ai vu des choses ! Mais ça... Mais ça, c'est la meilleure chose que j'ai vue.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Tout le monde dit ça, mais pour une raison quelconque, je te crois ! Tu l'aimes vraiment ?";
			link.l1 = "Eh bien, bien sûr, cela met très favorablement en valeur votre silhouette, bien que...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Oh, maintenant tu as tout gâché !";
			link.l1 = " ... bien que je ne doute pas qu' parmi les gens ordinaires, cela inspire la crainte !";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Je suis plutôt impressionnée par cette étrange habitude répandue parmi le peuple, qu'il soit commun ou non, de porter des vêtements européens denses sous une telle chaleur. Cela rend nos villages encore plus comiques... J'aime ma tenue, Charles. Dedans, je me sens belle, et c'est important pour une femme.";
			link.l1 = "Tu serais tout aussi belle sans cette tenue, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Attention, mon capitaine ! Dire de telles douceurs pourrait corrompre une pauvre fille !";
			link.l1 = "Si elle n'est pas contre, alors je ne suis pas contre non plus.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hihi ! Mieux vaut me poser des questions sur autre chose. J'aime quand tu deviens curieux.";
			link.l1 = "Alors, glissons une question sur votre costume. Je ne crois pas que les loups de mer puissent prendre un capitaine au sérieux dans une telle tenue.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "Et je ne crois pas que les loups de mer, en général, puissent voir une femme comme capitaine, donc ma tenue n'a probablement pas ajouté à mes problèmes. Ou peut-être n'a-t-elle pas eu le temps d'ajouter puisque c'est une nouveauté. Je l'ai cousue moi-même !\nAh-ha-ha ! Je portais l'un de ces... comment ça s'appelle ? Nos militaires les portent encore ! B-r-r... Voir l'un de ceux-là maintenant me rend malade.";
			link.l1 = "Uniformes ?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Oh,   exactement,   un uniforme ! Un uniforme rouge ! Comme ce type le porte.";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Oh, je suis désolée, Major, laissez-moi vous offrir un bon whisky irlandais comme... hic !... excuse.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles ne va pas avoir des ennuis, n'est-ce pas, Major? Dis-moi qu'il n'en aura pas, s'il te plaît!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Je suis si heureuse ! Buvons !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Upf. Regardez ce que j'ai!";
			link.l1 = "Helen... Tu comptes utiliser ça... pour te remonter le moral ?!.. N'y pense même pas ! La datura peut complètement subjuguer une personne, vider ses forces, écraser sa volonté ! Avant même que tu t'en rendes compte, tu es un cadavre vivant, et très rapidement, un mort...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, mais... en ce moment...";
			link.l1 = "Désolée, mais c'est non négociable. Je suis désolée d'être dure, mais ce n'est pas une plaisanterie. Je te retire ça. Je n'arrive pas à croire à quoi tu pensais... Tiens, bois ça et reprends-toi.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Je suis désolée, Charles. Tu as absolument raison, je sais. Une faiblesse passagère. Cela ne se reproduira plus. Merci de m'avoir sauvée de la tentation du diable...";
			link.l1 = " Oublions cela... Maintenant, dis-moi, comment as-tu réussi à gagner le respect dans la ville, maintenir de bonnes relations avec les officiers de la garnison, et te lier d'amitié avec les indigènes ? ";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Ils respectent Svensson, et une partie de ce respect me rejaillit. Notre petite ville survit uniquement grâce aux affaires de Jan. Il partage une partie des bénéfices de ses plantations de cacao avec les casaques rouges, et les Miskito lui doivent toute leur subsistance.";
			link.l1 = "Comment cela est-il arrivé?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Quand les Castillans étaient aux commandes, ils ne dérangeaient pas beaucoup les Indiens. Mais après avoir chassé les nobles Hidalgos, nos gens ont décidé de prendre le contrôle des forêts locales. Jan a résolu l'affaire de manière assez décisive à l'époque - il a même envoyé des gens à Londres ! Bien sûr, pas par bonté de cœur : extraire du cacao dans une forêt où chaque buisson vous déteste est une entreprise désespérée. Mais maintenant, les Indiens n'aident pas seulement Jan à faire de la contrebande de Porto Bello à Blueweld, mais ils abattent aussi leurs propres forêts pour une bouchée de pain. Bravo, Diable de la Forêt, bravo !";
			link.l1 = "On dirait que tu n'approuves pas entièrement ses méthodes.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "J'aime et respecte le peuple Miskito, mais je respecte aussi la stratégie de Jan. Nous ne vivons pas dans un conte de fées, mon capitaine.";
			link.l1 = "Hum... Je vois que votre relation avec Svensson est plus compliquée qu'elle ne le paraît à première vue...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "Alors changeons de sujet. Je voulais dire que tu t'intègres clairement dans cette compagnie, et qu'ils te considèrent comme l'un des leurs.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Il se trouve que c'est bien plus facile pour moi d'être en compagnie d'Indiens, de gitans, et d'autres marginaux respectables. Les ragoûts de maman, les feux de plage, et la passerelle du Rainbow - je me suis construit un petit monde douillet, Capitaine. Dommage que tout cela se soit effondré juste au moment où je pensais avoir tout compris.";
			link.l1 = "Le tonneau est presque vide... Une dernière tournée ?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "C'est si bon... Je suis heureuse que vous ayez accepté de passer du temps avec moi, Capitaine. J'en avais vraiment besoin. Je crois que vous aussi.";
			link.l1 = "Oui, cela fait un moment que je ne me suis pas détendue comme ça. Ce sera quelque chose à se rappeler!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Vous pensez probablement que le diable sait quoi à mon sujet en ce moment. Je suis une personne très renfermée par nature, Charles. Je voulais juste... bon sang, je voulais juste me sentir vivante ! Juste parler à quelqu'un !";
			link.l1 = "Et Gladys ? Jan ?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Tout ce que fait maman, c'est pleurer, et Jan semble être une personne différente maintenant. Peut-être que j'imagine des choses, je ne sais pas, mais c'est comme s'il avait honte de moi maintenant ? Pardonnez-moi, je... (renifle). \nÇa suffit, ma vieille. Désolée, je me suis un peu laissée emporter.";
			link.l1 = "Pas besoin de s'excuser. Je comprends tout, ou du moins je pense que je comprends.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Je dis tout cela parce que nous venons à peine de nous rencontrer, et je n'ai pas l'habitude d'être aussi ouverte, même avec ceux que je connais depuis longtemps. Ils m'appellent Rumba, apparemment pour mon caractère, mais comme vous pouvez le voir, c'est un abus de langage. Tout le rhum est-il parti ?";
			link.l1 = "Il y a un moment, et l'aube se lève déjà.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Je suis désolée, mon capitaine, si vous aviez d'autres attentes pour notre soirée. Je... je ne peux pas. Pas aujourd'hui.";
			} else {
				dialog.text = "Alors merci pour la soirée, Capitaine. Qui sait, peut-être que nous le referons.";
			}
			link.l1 = "Bien sûr, Hélène.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Merci de m'avoir amenée ici, Capitaine. Explorons les lieux, d'accord? Examinons mon héritage.";
			link.l1 = "N'es-tu pas déjà venu ici ?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "Nous ne le ferons pas. Je regrette déjà de t'avoir amené ici.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "Qu'en est-il de ce grand navire tiré à terre ?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Qu'en est-il de ce grand navire échoué sur le rivage ?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Attends, laisse une fille reprendre son souffle ! Es-tu vraiment ce Charlie Prince ?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Il y a eu une telle période dans ma biographie, oui. Es-tu impressionné ?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Oui, tu as raison. J'aimerais l'explorer, mais pour être honnête, Charles, cela me fait un peu peur. Allons-y.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Oh mon Dieu, oui ! Assure-toi de tout me raconter plus tard, d'accord ? Parce que je n'ai entendu que des histoires... très indécentes !";
			link.l1 = "Je te dirai tout... presque tout.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "Qu'en est-il de ce grand navire tiré à terre ?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Une masure exiguë et froide avec des exigences absurdes. Je me sens déjà comme dans un piège !";
			link.l1 = "Je vois que jusqu'à présent, vous n'êtes pas satisfait de la propriété potentielle ?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Non, Charles. Peut-être suis-je trop pointilleuse, mais pour l'instant, cela incarne tout ce que je crains et déteste. J'espère pouvoir le louer... Bien que je ne sois pas sûre où je vais dépenser l'argent.";
			link.l1 = "Ne sous-estime pas la valeur du loyer. Je n'ai pas de loyer, et souvent je dois trouver des moyens de payer mon équipage. Tu t'achèteras un nouveau navire, 'Arc-en-ciel II' - ça sonne bien, n'est-ce pas?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Il y a bien des façons de dépenser de l'argent pour soi-même. Commence par une épée personnalisée et une bouteille de vin excellent. Fais-toi plaisir, Helen, tu le mérites.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Merci, mon capitaine. Je suis heureuse de l'entendre. C'est particulièrement agréable de l'entendre pour la deuxième fois. Tu me connais bien.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Merci, mon capitaine. Je suis heureuse de l'entendre.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Penses-tu que je le mérite ? Je n'ai jamais dépensé d'argent pour de telles futilités, mais je suppose qu'il y a une première fois à tout. Je vois que tu ne cesseras pas d'essayer de me faire oublier la mer, hein, Capitaine ? Peut-être as-tu raison...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "Penses-tu que je le mérite ? Je n'ai jamais dépensé d'argent pour de telles babioles, mais j'imagine qu'il y a une première fois à tout.";
			}
			link.l1 = " ";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "En tout cas, l'inspection est terminée. Il ne semble pas y avoir de valeurs ici - la racaille a déjà réussi à tout piller, et je suis sûr que le deuxième étage est dans le même état.";
			link.l1 = "C'est comme si tu avais changé, Helen. La dernière fois que nous traînions ensemble, tu étais... je ne sais pas, plus ouverte ?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Rien n'a changé, mon capitaine, mais beaucoup de choses sont tombées sur les épaules d'une pauvre fille, haha ! Je ne voulais pas vous offenser. J'ai juste besoin de réfléchir à beaucoup de choses en ce moment. Vous savez, de tels virages dans la vie ne se produisent pas tous les jours. Et nous avons encore beaucoup de temps ensemble !";
				link.l1 = "Ravi de l'entendre ! Sortons d'ici.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "Je suis contente que nous ayons clarifié cela. Partons d'ici.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Oui?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hé, tout n'a pas été pillé ! Regarde, Hélène ! Ce sabre semble légendaire, étant donné que même la racaille locale a hésité à le prendre.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Non, rien.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Ouah, c'est... le légendaire sabre de Blaise lui-même ! Les pirates le respectaient trop pour prendre le sabre de chez lui même après sa mort. Ils ont pris l'argent et les objets de valeur, bien sûr, mais même les futurs pendards ont des restes d'honneur...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Merci pour cette observation perspicace, Charles. Tu as complètement gâché cet endroit à mes yeux, ha-ha !";
			link.l1 = "Je pense que ce sabre est désormais à toi. Blaise est ton soi-disant oncle...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Tu ajoutes encore plus d'horreur à cela, mon capitaine. Je... Je ne peux pas. J'ai peur que si je l'accepte, ma vie passée prenne complètement fin.";
			link.l1 = "Alors ne le prends pas comme une partie de l'héritage mais comme un cadeau d'un bel homme.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Qui cela pourrait-il être ? Je plaisante ! Merci d'avoir dissipé mes sombres pensées, mon capitaine. Je promets de m'entraîner beaucoup pour être digne de cette lame !";
			link.l1 = "Tu mérites la meilleure arme, Hélène. Allons-y, nous avons fini ici.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Wow, c'est... le sabre légendaire de Blaise lui-même ! Les pirates le respectaient trop pour prendre le sabre de sa maison même après sa mort. Ils ont bien sûr pris l'argent et les objets de valeur, mais même les futurs pendards ont des restes d'honneur.\nJe... je ne peux pas. J'ai peur que si je l'accepte, ma vie passée prenne fin complètement.";
			link.l1 = "Alors ne le prenez pas comme faisant partie de l'héritage, mais comme un cadeau d'un bel homme.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Qui cela pourrait-il être ? Je plaisante ! Merci d'avoir dissipé mes sombres pensées, mon capitaine.";
			link.l1 = "Tu es digne de la plus fine des armes, Helen. Je suis heureux que cela te plaise.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Je promets que je m'entraînerai beaucoup pour être digne de cette lame !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Mon capitaine ! Charlie !";
			link.l1 = "Charlie ? C'est nouveau ! Heureuse de te voir, cher.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "J'ai accidentellement fait une gaffe, ha ! Heureuse de te voir aussi...";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Eh bien, pour la solidarité fraternelle ! Mon capitaine, je... j'étais vraiment inquiète et tu m'as tellement manqué !";
			link.l1 = "Alors, pourquoi as-tu dû rentrer chez toi en courant ?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "A... Oh, c'est vrai ! J'ai un petit cadeau pour toi, tiens !";
			link.l1 = "Trois amulettes... Hélène, pourquoi ? Vouliez-vous me suivre ?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Viens ici, imbécile !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Ne t'avise pas de gâcher cet instant - je l'ai imaginé toute ma vie !";
			link.l1 = "Je ne le ferai pas, Hélène.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Tu as attendu toute ta vie pour me rencontrer? Flattée!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, il y a quelque chose... Sur l'île de la Justice, j'ai rencontré une femme, et...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Merde alors ! Tu me diras tout, tout ! Je t'attendrai sur le navire, mon capitaine !";
			link.l1 = "Attends !...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Imbecile ! Tu veux m'offenser ? Très bien, je suis offensée ! Ha-ha ! Je vais retourner au navire pour l'instant, avant que Danny ne se moque davantage de moi...";
			link.l1 = "Attends !...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Imbécile ! Je t'avais demandé de ne pas gâcher le moment ! Rencontré... eh bien, tu as rencontré - je ne vois pas encore de bague à ton doigt. Mais ne crois pas t'en tirer à si bon compte - j'attendrai une histoire détaillée quand tu reviendras sur le navire.";
			link.l1 = "Attends !...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Mon capitaine, quelles sont les nouvelles ? Je peux deviner à votre visage pâle que l'avocat a décidé de vous lancer plus de problèmes au lieu d'aider.";
			link.l1 = "Tu as raison, Helen. Loxley a exigé une avance impressionnante, et cette affaire me coûtera un joli paquet. Je vais aller secouer Jan - j'en ai assez ! On dirait que les Frères ont décidé de me refiler toutes leurs dépenses !";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Il n'y a pas de malice là-dedans, Charles. C'est juste comme ils sont - ils ne lèveront pas le petit doigt à moins d'y être obligés. Je suis sûre que Jan vous aidera, et je ne resterai pas non plus les bras croisés.";
			link.l1 = "Je sais, Hélène. Dis-moi ce que tu as en tête.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Je travaillais pour Jan - trafiquant du bois précieux partout dans le Maine. Mais je suis une fille débrouillarde, et j'ai mis quelque chose de côté pour moi pendant tous ces voyages.";
			link.l1 = "Et Jan ne l'a pas découvert ? Astucieux !";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "J'avais un bon trésorier. Bref, j'ai accumulé une somme décente, et je l'ai cachée non loin d'ici. Vous allez voir Jan maintenant ? Alors allons visiter San Juan del Norte. Il y a une grotte à proximité, et nous aurons juste besoin de quelques marins pour nous aider, afin de ne pas tout porter nous-mêmes.";
			link.l1 = "Tu as déjà tout compris, n'est-ce pas ? Merci, Hélène, nous passerons sûrement si nous avons le temps.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Mon capitaine, quelles sont les nouvelles ? Je peux dire à ton visage pâle que l'avocat a décidé de te lancer encore plus de problèmes au lieu de t'aider.";
			link.l1 = "Tu as raison, Hélène. Loxley a exigé une avance impressionnante, et l'affaire elle-même va me coûter une jolie somme. Je vais aller secouer Jan - j'en ai assez ! On dirait que la Fraternité a décidé de me refiler toutes leurs dépenses !";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Tu pensais être dans un conte de fées ? Ne t'inquiète pas, nous sommes tous dans le même bateau ici, et je vais t'aider. Après tout, j'ai droit à un héritage, n'est-ce pas ?";
			link.l1 = "C'est vrai... Dis-moi, à quoi penses-tu !";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "J'ai quelque chose caché à San Juan del Norte. Il y a une grotte à proximité - nous aurons juste besoin de quelques matelots pour ne pas avoir à tout porter nous-mêmes.";
			link.l1 = "Tu as déjà tout compris, n'est-ce pas ? Merci, Hélène, nous viendrons sûrement vous rendre visite si nous avons le temps.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "C'est ici, Charles ! Mais tu devras y aller seul - je déteste les grottes !";
			link.l1 = "Comme tous les espaces clos, je sais, Hélène. Attends-moi ici.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Nous avons un problème ! Une escouade de soldats arrive par ici, et ils ont l'air menaçants. Fais attention, Charles, ce ne sont pas de simples gardes-côtes - il y a un officier français parmi eux ! Je t'en supplie, ne fais rien de stupide !";
			link.l1 = "Quand ai-je jamais fait quelque chose de stupide?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, la deuxième option semble plus alléchante, mais j'espère que tu n'es pas trop fier de toi, Charles ?";
			} else {
				dialog.text = "Je ne peux pas dire que je suis surprise, Charles...";
			}
			link.l1 = "Bonjour, ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Tu as fini ? Maintenant, c'est à mon tour de parler !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Je m'appelle Helen MacArthur ! Capitaine, vous savez qui je suis et pour qui je travaille ! Informez vos hommes, surtout ce joli imbécile allongé par terre, des résultats d'aujourd'hui, que je vais maintenant annoncer !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protestez ? Peu m'importe si vous écrivez à Cromwell lui-même. D'abord, Monsieur de Maure n'a pas perdu son honneur aujourd'hui.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Deuxièmement, le colonel de Tavann a été abattu par une fille dans une tenue très épicée pour l'avoir traitée de prostituée.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Troisièmement, vous retirez immédiatement vos soldats et vous oubliez ce qui s'est passé, à moins que vous ne vouliez que le Diable de la Forêt en soit informé.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Pas de questions, je vois. Passez une bonne journée, Capitaine.";
			link.l1 = "Bon Dieu, Hélène, tu es en feu !";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Plus tard, Charles. Sortons d'ici avant qu'ils ne se remettent du choc. Je tremble de partout aussi. Pourrions-nous parler à Blueweld ?";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Sauvons-nous d'ici avant qu'ils ne se remettent du choc. Nous devons toujours récupérer le bois de fer, tu te souviens ? Nous pourrons parler à Blueweld.";
			link.l1 = "Wow ! Pas même un mot de félicitations ? Très bien, allons-y.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Enfin, chez moi...";
			link.l1 = "Que penses-tu de ce qui s'est passé ?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Je ne comprends pas les duels. Un passe-temps d'hommes, se terminant souvent par deux cadavres, et les jours de chance, même plus. Et l'honneur... Je crois que l'honneur repose sur le désir d'éviter le conflit jusqu'à la toute fin, car il en vaut rarement la peine. Ha ! Écoute-moi donc - je débite des sottises !";
			link.l1 = "C'est une perspective intéressante, Hélène. Bien que tout le monde ne serait pas d'accord avec ça.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Quel dommage que vous soyez tombé dans leur piège. Le colonel était clairement obsédé, et les autres ne cherchaient qu'un spectacle et des ragots. Bon, je ne vais pas en rajouter - vous en avez assez eu pour aujourd'hui.";
			link.l1 = "Oui, après les duels, il y a toujours un sentiment de vide. Assez d'aventures pour aujourd'hui. Que veux-tu faire ensuite ?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ah! Je voulais juste dire que je suis fière de nous. Tu as montré un vrai courage aujourd'hui, mon capitaine. Tu n'as pas cédé à l'hystérie de l'équipage qui voulait juste te commander pour une fois. Tu as tenu bon contre la prétention de l'uniforme rouge et l'obsession du bleu. Le colonel cherchait clairement la mort mais n'a récolté rien de plus qu'une blessure dans un endroit inapproprié, ha-ha !";
			link.l1 = "Merci, Helen. Tu nous as brillamment détournés du coup, comme un vrai officier de marine. Es-tu fière de toi ?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Oui, j'avais besoin de ça. C'est juste dommage que ce soit un uniforme bleu et non rouge, mais au moins la personne qui le portait a eu ce qu'elle méritait.";
			link.l1 = "Cet individu est en effet sans importance, je l'admets. Assez d'aventures pour aujourd'hui. Que veux-tu faire ensuite ?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Je rentre chez moi, mon capitaine. Ma maman... Gladys me manque. Dommage qu'elle soit à la maison en ce moment, sinon je t'aurais invité!";
			link.l1 = "En effet, c'est bien dommage !";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Ne sois pas si contrariée. Bientôt, ma chère. En attendant...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, celui-ci est encore meilleur que notre premier. Tu te souviens ? Près de l'idole ?";
				link.l1 = "Ce n'est pas quelque chose qu'on oublie, mon cher.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Ne t'avise pas de gâcher ce moment - je l'ai imaginé toute ma vie !";
				link.l1 = "Je ne le ferai pas, Hélène.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Vous avez attendu toute votre vie pour me rencontrer ? Flattée !";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = " Ohh ! Ressaisis-toi, ma fille ! Jusqu'à ce que nous nous rencontrions à nouveau, mon capitaine. ";
			link.l1 = "Jusqu'à ce moment-là, Hélène.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Bon sang, oui ! Nous nous reverrons bientôt, mon capitaine.";
			link.l1 = "Jusqu'à ce que nous nous retrouvions, Helen. Oh Dieu, quelle fille...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Imbecile ! Tu veux m'offenser ? Très bien, je suis offensée ! Ha-ha ! On se reverra bientôt, mon capitaine.";
			link.l1 = "Jusqu'à notre prochaine rencontre, Hélène. Oh Dieu, quelle fille...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Je rentre à la maison, Capitaine. Je suppose que le problème d'argent avec l'avocat est maintenant réglé ? Nous avons des obstacles difficiles devant nous, alors essayons de rester à l'écart des ennuis à partir de maintenant. Les ennuis viendront à nous d'eux-mêmes.";
			link.l1 = "Ouah, vraiment ?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Désolée d'être directe, Cap. Mon destin se joue aussi maintenant, vous savez.";
			link.l1 = "Je sais, je vais essayer de gérer cela aussi dignement que possible. À bientôt sur le navire, Hélène.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Aye aye, Capitaine !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Quelle est la suite ? Je vais te montrer.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, celui-ci est encore meilleur que notre premier. Tu te souviens? Près de l'idole?";
				link.l1 = "Ce n'est pas quelque chose qu'on oublie, mon cher.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Ne t'avise pas de gâcher ce moment - je l'ai imaginé toute ma vie !";
				link.l1 = "Je ne le ferai pas, Hélène.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Vous avez attendu toute votre vie pour me rencontrer ? Flatté !";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Nom de Dieu ! Oh là là ! Gladys n'est pas à la maison maintenant. Tu veux entrer ?";
			link.l1 = "Tu m'invites chez toi ? Et que ferons-nous ?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Non, Helen. Une autre femme m'attend sur l'île de la Justice. Je ne peux pas lui faire ça.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Une autre fois, mon cher. J'en ai vraiment envie, mais aujourd'hui m'a presque achevé. Nous nous rattraperons et compenserons le temps perdu au centuple.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Merde, oui ! Waouh ! Gladys n'est pas chez elle maintenant. Tu veux entrer ?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Non, Helen. Une autre femme m'attend sur l'île de la Justice. Je ne peux pas lui faire ça.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Une autre fois, mon cher. J'en ai vraiment envie, mais aujourd'hui m'a presque achevée. Nous nous rattraperons et compenserons le temps perdu au centuple.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Vous m'invitez ? Et que ferons-nous ?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Imbécile ! Tu veux m'offenser ? Très bien, je suis offensée ! Ha-ha ! Tu vas devoir te racheter, mon capitaine. Oh là ! Gladys n'est pas à la maison en ce moment. Tu veux entrer ?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Non, Hélène. Une autre femme m'attend sur l'île de la Justice. Je ne peux pas lui faire cela.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Une autre fois, mon cher. J'en ai vraiment envie, mais aujourd'hui m'a presque achevée. Nous nous rattraperons et compenserons le temps perdu au centuple.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "M'inviter chez vous ? Et que ferons-nous ?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ah, donc je ne suis pas assez habile dans l'art de la séduction ? Et elle l'est ? Qui est-elle ?";
			link.l1 = "Elle s'appelle Mary Casper, et je l'aime.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Ce rouquin dans l'uniforme rouge ? Dans l'uniforme rouge... Eh bien, si j'avais besoin d'un signe, le voilà. Ce n'est pas censé être. Et ne t'inquiète pas, Capitaine, cela n'affectera pas mon service sur ton navire.";
			link.l1 = "Je suis désolé, Hélène.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Oh, mon capitaine ! C'est dangereux de laisser une femme dans un tel état ! Je vous tiens à votre parole, et maintenant courez... J'ai besoin d'être seule maintenant et d'essayer de résoudre mon problème... par moi-même ! À bientôt sur le navire !";
			link.l1 = "Quelle fille !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Ne t'inquiète pas, ma chère, je te guiderai si tu te perds.";
			link.l1 = "Eh bien... en avant !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Ne dites rien, je vous en prie.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... bien sûr, jusqu'à aujourd'hui, ma compréhension de ce sujet était uniquement basée sur les conversations vulgaires de l'équipage de la 'Rainbow', si tant est qu'on puisse appeler cela des conversations, bien sûr.";
			link.l1 = "Et comment cela s'est-il passé ? La réalité a-t-elle répondu à vos attentes ?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Je l'ai beaucoup apprécié, mais j'ai l'impression de ne pas l'avoir pleinement vécu. Et comment...";
			link.l1 = "Laisse-moi te montrer !  Continuons-nous ?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Ah, maintenant je comprends ! C'était tout simplement merveilleux, mon capitaine !";
			link.l1 = "Tu m'as surpris, c'est le moins qu'on puisse dire !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha ! C'est une bonne celle-là, c'est sûr ! Maintenant elle va soit se boucher les oreilles avec de la cire, soit courir vers la plus haute plateforme du fort !";
			link.l1 = "C'était inattendu mais très drôle, ah-ha-ha !";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Prêt, mon capitaine ?";
			link.l1 = "Deja?! Non, Helene, aie pitie de moi, je t'en prie. L'apparition soudaine de Gladys n'a certainement pas aide l'atmosphere.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Eh bien, que pouvez-vous faire... Bien que...";
			link.l1 = "Non, non, baissez vos voiles !";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "D'accord, restons ensemble un moment. Notre avenir est si brumeux et effrayant, mais pour la première fois depuis longtemps, je n'ai peur de rien d'autre. Je sais que de nouvelles craintes surgiront, mais pas aujourd'hui. Pas aujourd'hui, mon capitaine.";
			link.l1 = "Pas aujourd'hui, mon cher. Pas aujourd'hui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Permission de parler, Capitaine ?";
			link.l1 = "Oui, Hélène ?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Je connais cet Oeil de Serpent - c'est un bon homme, mais un peu bizarre. Il envoie régulièrement des gens en quête pour je ne sais quoi. Je vois que tu as eu cet honneur douteux aussi.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "C'est vrai, je dois lui apporter trois amulettes, sinon il ne pourra pas m'aider à atteindre l'endroit de Hawk. Mais tu sais ce qui est drôle ? Je les avais déjà avec moi ! Peut-être qu'il le savait depuis le début ?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "C'est ça, je dois lui apporter trois amulettes, sinon il ne pourra pas m'aider à atteindre l'endroit de Hawk. Je n'arrive pas à comprendre où les trouver maintenant, et le temps presse.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Oh, quel dommage ! Je suis heureuse que tu n'aies pas eu à courir après ces amulettes chez les gardiens de phare, mais j'espérais qu'une fois je pourrais t'être utile, espérais me prouver.";
			link.l1 = "Balivernes, Hélène. Tu n'as rien à me prouver.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Je t'aiderai ! J'avoue, j'espérais qu'une fois je pourrais t'être utile, espérais faire mes preuves.";
			link.l1 = "Balivernes, Helen. Tu n'as rien à me prouver.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Néanmoins, je veux t'aider. Tiens, prends la clé de ma chambre... Je veux dire, du coffre dans ma chambre ! Il n'y a pas grand-chose, mais pour toi, cela sera utile. Et... Charles, essaie juste de ne pas éclater de rire maintenant !";
			link.l1 = "Hum, je n'allais pas le faire. Je vois que tu t'intéresses à ces choses-là ?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Je suis marin, mon capitaine, tout comme vous. Dans notre métier, nous devons tout faire pour mettre la Dame Chance de notre côté.";
			link.l1 = "Merci, Hélène. Je l'apprécie vraiment.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Chéri, j'ai un cadeau pour toi !";
			link.l1 = "Je vois, le voilà - debout et souriant !";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, arrête ça ! Une fois, j'ai livré un bon lot de soie au charpentier local, donc maintenant il me doit une révision complète du navire. J'avais pensé lui confier 'Arc-en-ciel' pour ce travail, mais cela n'était pas censé être. Ton navire, par contre, pourrait vraiment bénéficier de tels soins, tu ne crois pas ?";
			link.l1 = "En effet, un cadeau splendide, Helen - tout à fait dans tes cordes !";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Je suis contente que cela te plaise. Va le voir quand tu veux et dis-lui que je t'ai envoyé. Ils feront de leur mieux.";
			link.l1 = "Certainement!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Permission de parler, mon capitaine ?";
			link.l1 = "Bien sûr, mon cher.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Votre dame vous manque et exige de l'attention. Puis-je demander à organiser une chambre pour elle et lui consacrer un peu de temps","Rapport: votre présence est requise dans un lit à la taverne locale. Juste cinq minutes de votre temps, mais l'équipage espère que vous resterez plus longtemps !","Mutinerie sur le navire, mon capitaine ! Je suis chargée de vous remettre une marque noire en privé. Venez avec moi immédiatement !");
			link.l1 = "Hi-hi, ahem! Votre demande est accordée, Officier Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Pas aujourd'hui, cher. Il se passe trop de choses en ce moment.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Oh, et que voudrais-tu qu'une pauvre fille fasse, hein ? Très bien, mon cher, une autre fois alors.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Vous n'avez pas besoin de me le demander deux fois ! Bien sûr, allons-y !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Je te jetterai par-dessus bord sur-le-champ !";
			link.l1 = "Eh, eh, eh ! Calme-toi, ma chère !";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Viens ici, coquin !";
			link.l1 = "Je plaisante, Hélène ! Je ne voulais pas te vexer !";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Vraiment ? Avale un rigolo...";
			link.l1 = "Tu es la plus belle, et je t'aime à la folie !";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Va-t'en, Charles.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Tu es toi-même une catin ! Sois heureuse que Jan ait fait de toi une femme honnête, sinon tu continuerais à écarter les jambes pour chaque passant !";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Salope ! Allons-y, Charles !";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "La machette me va parfaitement à la main ! Je ne sais pas comment l'expliquer... J'ai toujours eu du mal avec d'autres types d'armes blanches, comme les rapières et les épées. Mais cette machette, c'est une autre histoire ! Elle est extraordinaire ! Merci, Charles !";
			link.l1 = "Le destin a une façon de nous trouver. Je suis content pour toi, Helen !";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Sauve tes histoires pour quelqu'un d'autre, elles ne fonctionneront pas sur moi. Ai-je l'air d'une idiote amoureuse et naive ? Je veux dire, JE SUIS follement amoureuse de toi, mais m'appeler une idiote serait exagéré\n Écoute, chéri, fais comme bon te semble, mais garde à l'esprit que tu ne trouveras pas meilleure femme que moi. Si tu veux la chercher dans les bordels, vas-y, mais alors je disparaîtrai de ta vie pour de bon.";
			link.l1 = "Helen, je...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Je comprends tout, Charles. Tu n'aimes que moi, et ce ne sont que des pulsions naturelles. Tu sais quelle est ma pulsion naturelle ? Le respect de mon homme. Une femme peut ne pas se satisfaire uniquement d'amour, mon cher. Oublions ce malentendu pour l'instant, mais réfléchis un peu à mes mots. D'accord ?";
			link.l1 = "D'accord, Hélène.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Tu sais comment ça se passe. Laisse une fille se calmer d'abord.";
			link.l1 = "Soupir...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... Je me souviens de lui. Il attendait toujours mon arrivée à Port Royal et était un romantique invétéré. J’aimais passer du temps avec quelqu’un d’éloigné de la mer – tous ces poèmes et sérénades... C’était quelque chose de nouveau. Un éclat d’un monde que je n’avais jamais connu.\nFrancis était riche, intelligent et séduisant – un excellent parti. N’importe quelle fille d’ici aurait perdu la tête pour lui, mais à l’époque, je me souciais surtout de garder l’Arc-en-ciel à flot.";
			link.l1 = "Il semble que l’âme sensible d’un poète n’ait pas supporté ton refus. Dans toutes ses lettres, il ne parlait que de toi, se remémorant vos rencontres. Je peux te remettre tout ce qu’il t’a légué, si tu le souhaites.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Je ne savais pas qu’il était malade. Tout cela semble bien absurde maintenant. Quant à son cadeau... J’en ai assez des testaments et des héritages. Crois-moi, j’ai tout ce dont j’ai besoin – et même plus. Garde-le plutôt.";
			link.l1 = "D’une manière ou d’une autre, son héritage te profitera toujours – ce qui signifie que, sans le vouloir, j’ai accompli son dernier souhait. Une histoire fascinante.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
