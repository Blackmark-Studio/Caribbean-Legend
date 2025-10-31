// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Bonjour, monsieur. Qu'est-ce qui vous amène chez nous ?";
					link.l1 = "Bonjour, Abigail. Mon nom est "+GetFullName(pchar)+"Je suis un capitaine travaillant pour le bien de la République et la Compagnie néerlandaise des Indes occidentales.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Mon Dieu, as-tu trouvé l'argent de mon père ? Est-ce vrai ? Ah, je suis si heureux ! Va vite voir mon père, il veut te parler. Va le voir !";
					link.l1 = "Je suis en route, madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Vous nous avez sauvés d'un désespoir total, capitaine ! Je vous suis tellement reconnaissant ! Maintenant, le bon nom de la famille Shneur peut être restauré !";
					link.l1 = "Je ne fais que mon devoir de gentilhomme, madame. J'espère qu'il n'y a plus rien qui vous empêche d'épouser mon patron.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Vous avez besoin de quelque chose, capitaine ?";
				link.l1 = "Pas maintenant, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Salut Sainte Reine, notre vie, notre douceur et notre espoir. Vers vous nous crions, pauvres enfants bannis d'Ève. Vers vous nous élevons nos soupirs, en pleurant et en gémissant dans cette vallée de larmes... oh monsieur, vous m'avez surpris ! Qu'est-ce qui vous amène ici ?";
					link.l1 = "Je vous demande pardon, Abigail je présume ? Richard Fleetwood m'a envoyé...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Voulez-vous quelque chose, capitaine ?";
				link.l1 = "Pas maintenant, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Que se passe-t-il ici? Quel est ce bruit? Papa, qui est cet homme étrange?";
					link.l1 = "Bonne journée, madame. Abigail Schneur, je présume ? Je suis heureux de vous voir. Vous devez excuser mon impertinence, mais j'ai ici une lettre urgente qui vous est adressée de... eh bien, j'aimerais vous dire, mais votre cher père refuse même de me laisser entrer chez vous, sans parler de vous remettre ce message.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, te voilà Charles. Je suis prêt à te suivre n'importe où !";
					link.l1 = "Allons-y alors.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Sommes-nous déjà à Saint-Jean, Charles ? Verrai-je bientôt Richard ?";
					link.l1 = "Oui, madame, nous sommes à St. John's. Malheureusement, Richard n'est pas en ville pour l'instant, il a reçu l'ordre de patrouiller près de la Barbade il y a deux jours. Ne vous inquiétez pas, il devrait revenir dans une semaine.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles ! Je suis si heureux de te voir ! Des nouvelles de Richard ?";
					link.l1 = "Hélas, ma chère madame. Richard a dû rester à Bridgetown pour un moment pour une mission secrète et importante, cela a un rapport avec les Hollandais. Je suppose que Richard vous a dit ce qu'il fait pour vivre, n'est-ce pas?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles ! C'est toi ! Tu es enfin de retour !";
					link.l1 = "Salutations, madame. Je suis heureux de vous voir.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, je suis enfin chez moi ! Je suis si heureux de revoir papa ! Charles, merci pour tout ce que tu as fait pour moi !";
					link.l1 = "Je vous en prie, il n'est point besoin de tels discours, madame. Je ne fais que mon devoir de gentilhomme envers une dame en détresse.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papa, si tu te souviens de quoi que ce soit, dis-le s'il te plaît ! Charles, il est... on peut lui faire confiance. J'ose dire qu'il est le seul qui puisse nous aider !";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Je prierai pour toi nuit et jour ! Dis-moi... dis-moi que tu le feras ! Que tu trouveras l'île !";
					link.l1 = "Je ferai ce que je peux, madame.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, Charles ! Vous êtes de retour ! Dites-moi vite, avez-vous trouvé l'île ? Je ne peux guère attendre plus longtemps !";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Oui, Abi. J'ai trouvé l'île et l'argent de ton père. Je suis ici pour te le rendre.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Hélas, madame. Je n'ai pas réussi à trouver ni le capitaine Keller ni votre île. J'ai fait ce que j'ai pu, mais...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, c'est toi Charles ! Besoin de quelque chose ? Puis-je t'offrir un café ?";
				link.l1 = "Non, rien. Je vous en prie, ne vous dérangez pas.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bonjour, monsieur. Que voulez-vous?";
			link.l1 = "Rien, madame. Je dois vous demander pardon. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Je suis honoré de vous rencontrer, Capitaine "+GetFullName(pchar)+". J'ai entendu toutes sortes d'histoires à votre sujet de la part des autres dames de la ville. Vous êtes l'homme qui a capturé le navire fantôme pirate et l'a amené comme prix à Willemstad. Dites-moi capitaine... est-il vrai que ce navire était sous le commandement de... Richard Fleetwood?";
			link.l1 = "Tout ce que vous avez entendu est vrai, madame. J'étais aussi choqué que quiconque de découvrir la vérité. C'est un scandale ! Un officier de la marine du Commonwealth anglais pillant les marchands de sa propre nation comme un pirate ordinaire ! Ce vaurien a tenté de dissimuler ses actes infâmes en prétendant être un 'vaisseau fantôme' renégat soutenu par la Compagnie néerlandaise des Indes occidentales. Il a utilisé cette couverture pour accuser la Compagnie et attaquer également les navires néerlandais.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "J'ai la tête qui tourne... C'est dur d'entendre de telles horreurs, capitaine. Je connaissais personnellement Richard Fleetwood, je n'aurais jamais pensé qu'il...";
			link.l1 = "Madame, je suis informé par mon patron Lucas Rodenburg de votre voyage à Curaçao depuis Recife. Maintenant c'est clair. Fleetwood a coulé votre navire puis est revenu pour vous 'sauver', vous et votre père, de l'abandon sur cette île perdue. J'ai lu moi-même le journal du pirate, il a noté chaque détail dans son livre de bord.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Quel cauchemar... Il semble que mon papa avait raison après tout. Il n'a cessé de me dire que Richard était ce pirate qui était à l'origine de tous nos malheurs. Je devrais être heureux que la vérité soit révélée... ah, je suis désolé, capitaine. C'est juste tellement à assimiler pour ma pauvre tête... que veut un homme aussi important que vous d'une fille ordinaire ?";
			link.l1 = "Abigail, je suis ici à cause d'une affaire très compliquée et délicate. Voulez-vous m'écouter ?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Bien sûr, monsieur. Je suis tout ouïe.";
			link.l1 = "Comme je l'ai dit, je sers la Compagnie. Lucas Rodenburg n'est pas seulement mon commandant militaire, mais aussi un bon ami. Il m'a envoyé vers vous avec un message. Ce serait le plus grand bonheur pour vous de consentir à sa proposition de mariage. Je suis ici pour vous demander d'épouser mon protecteur. Il est prêt à faire n'importe quoi dans le monde pour votre bonheur.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Ah, capitaine ! Je vois maintenant pourquoi Monsieur Rodenburg n'était pas prêt à le faire lui-même... Mon pauvre papa serait ravi mais moi...";
			link.l1 = "Madame, je vois bien que quelque chose vous tracasse. Doutez-vous de la sincérité de Monsieur Rodenburg ? Peut-être pourrais-je vous aider à changer d'avis ?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = " Oh non capitaine, je n'ai aucun doute sur la sincérité de Monsieur Rodenburg. Lucas a tant fait pour moi et mon papa, je ne sais pas ce qui nous arriverait s'il ne veillait pas sur nous. Mais s'il vous plaît, vous devez comprendre ma position !\nMa famille n'est pas les Rothschild, mais nous n'avons jamais été pauvres. La famille Shneur est bien connue parmi les maisons bancaires d'Europe pour notre fortune... mais maintenant ce terrible pirate nous a ruinés ! Je ne peux plus supporter ces méchancetés qui se répandent dans notre dos. Chaque commère et servante de cette ville pense que je ne suis après Monsieur Rodenburg que pour son argent. 'Comme une vraie Juive', disent-elles. Les cruelles ! Si seulement mon père se souvenait de l'emplacement de l'île ! Il y a caché ce qui reste de notre fortune familiale pour la sauver des mains de ces maudits pirates qui ont assassiné mes sœurs et mon frère !\nMais mon pauvre père n'est pas marin, il ne peut tout simplement pas se rappeler où se trouvent cette île et notre argent familial ! Parlez à mon père, capitaine, je vous en prie ! Peut-être pourra-t-il se souvenir de quelque chose qui pourrait être utile à vos sens aguerris. Trouvez cette île et notre fortune, je vous en supplie ! Vous sauverez une pauvre fille de la honte et de l'ignominie !";
			link.l1 = "Très bien, Abigail. Je parlerai à ton père. Aie foi, ma fille, je ferai ce que je peux.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Merci, monsieur. Je prierai pour vous nuit et jour. Que le Dieu de nos pères soit avec vous !";
			link.l1 = "Adieu, Abigail. Je reviendrai avec de bonnes nouvelles, je le jure.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, oui! Mynheer Rodenburg est un homme honorable et gentil. Je lui donnerai mon consentement sans hésiter et je serai heureuse de l'appeler mon mari.";
			link.l1 = "Alors je considère ma mission accomplie. Je dois maintenant aller voir Monsieur Rodenburg et lui annoncer la bonne nouvelle. Je vous souhaite sincèrement du bonheur, madame.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard vous a envoyé ?! Sainte Marie, merci ! Ah, monsieur ! J'ai entendu dire que le pauvre Richard était blessé et proche de la mort. Est-ce vrai ? Dites-moi, est-il vivant ?! Est-il en bonne santé ?!";
			link.l1 = "Richard est vivant et... plutôt en bonne santé. Voici d'abord les mauvaises nouvelles : il est un peu amoché et il a temporairement perdu la vue, mais il est en voie de guérison. Maintenant, les bonnes nouvelles : Richard veut que tu lèves l'ancre avec lui pour l'Angleterre où vous vous marierez. Son temps aux Caraïbes est terminé et il attend ta réponse.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, mon cher messager, dis à Richard que pour notre bonheur je suis prête à le suivre où il veut. Mais j'ai peur que notre fuite ne tue mon pauvre père... Monsieur, je suis désespérée et je ne sais que faire. J'aimerais que Richard puisse trouver cette maudite île et le coffre avec notre or familial... Peut-être que cela réconforterait d'une manière ou d'une autre mon papa en mon absence.";
			link.l1 = "Je vois... Ma mission était de vous livrer à Antigua, mais cela complique quelque peu les choses. Si je trouve l'île et le coffre et vous les apporte, viendrez-vous alors avec moi à St. John's et voir Richard ?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Oh oui monsieur, je me souviendrais de vous dans nos prières familiales ! Je nommerais notre premier fils d'après vous ! Merci beaucoup, capitaine ! Je prierai pour vous ! Allez et que le Christ et la Sainte Mère soient avec vous !";
			link.l1 = "Je ne vous ferai pas attendre trop longtemps, madame. Je reviendrai bientôt.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... Vous avez une lettre de lui ? Oh papa, ne soyez pas si dur avec nos invités ! Vous me faites honte avec vos fantasmes névrotiques ! Monsieur, s'il vous plaît, suivez-moi, je veux vous parler.";
			link.l1 = "Merci, mademoiselle. Heureux de voir quelqu'un dans cette maison parler avec bon sens.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Pardonnez mon père, monsieur. C'est vraiment un homme bon et aimable, mais nos...malheurs l'ont brisé.";
			link.l1 = "Tout va bien, maîtresse, je comprends. Permettez-moi de me présenter, je suis Charlie le... Knippel. Je suis ici sur ordre de Richard Fleetwood, il veut que je vous amène à lui. Voici, s'il vous plaît, lisez la lettre.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(lisant). Oh, Dieu! Il a décidé... de rendre à mon père tout son argent perdu! Quelle générosité! Cher, doux Richard! Monsieur, vous apportez de bonnes nouvelles comme Gabriel lui-même! Richard, où est-il? Est-il à Curaçao?";
			link.l1 = "Non, mademoiselle. Il y a eu une tentative sur sa vie et il a été grièvement blessé. Il est à Antigua maintenant... vous n'avez pas terminé la lettre.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Sainte Marie conçue sans péché, priez pour nous qui avons recours à vous ! Dites-moi, est-il en sécurité ? Sa blessure est-elle grave ?";
			link.l1 = "N'ayez pas peur comme ça, mademoiselle ! Richard n'est pas le genre d'homme à laisser des vauriens le tuer ainsi. Il se repose et se rétablit maintenant. Il veut que je vous emmène à lui. Ensuite, vous naviguerez ensemble vers Londres... s'il vous plaît, terminez la lettre, mademoiselle, vous allez trop vite.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, oui...Je suis désolé (en train de lire). Monsieur Knippel, je suis prêt à naviguer avec vous. J'ai besoin d'un jour pour emballer mes affaires et parler avec mon papa. Revenez demain et je partirai avec vous.";
			link.l1 = "D'accord, madame. Je serai ici demain. Ne vous inquiétez pas, moi et mon équipage vous protégerons de tout danger pendant notre voyage.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, quel dommage. Mais je pense que je peux attendre une semaine de plus comme j'ai attendu auparavant...";
			link.l1 = "Bien dit, mademoiselle. Et pour alléger votre attente, je propose d'échanger cette cabine plutôt austère contre la maison de mon ami. Vous y trouverez un lit moelleux et de bons plats préparés pour vous.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Tu es si aimable, Charlie. Merci. Ce sera bon d'avoir la terre sous mes pieds... Je me sens assez mal après tout ce tangage sur les vagues.";
			link.l1 = "Suis-moi, je vous prie, mademoiselle.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Je suis ravi de vous rencontrer, John. Merci pour votre aimable hospitalité, messieurs !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Oh Charlie, j'ai vu Richard seulement quelques fois et il ne m'a pas beaucoup parlé de ce qu'il fait.";
			link.l1 = "Je suis assez surpris qu'il dissimule un si grand secret à la femme qu'il aime... Mademoiselle, Richard n'est pas qu'un simple capitaine. Il est aussi un agent spécial du Conseil privé anglais. Un homme très important chargé de missions délicates ordonnées directement par le Lord Protecteur lui-même. En ce moment, son devoir concerne la destruction du pouvoir commercial de la Compagnie néerlandaise des Indes occidentales dans les Caraïbes.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Monsieur, de quoi parlez-vous?";
			link.l1 = "Oui, mademoiselle. Votre bien-aimé Richard - mon ami - est un homme très important. J'ai toujours été fier d'être son ami, mais il est devenu très secret, même avec moi. Il est évident qu'il est en mission secrète. Je suis vraiment désolé que cette mission ne lui permette pas de vous rencontrer.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, tu me fais peur. Es-tu sûr qu'il va bien ?";
			link.l1 = "J'en suis sûr. Je... je n'approuve pas la façon dont il te traite en ce moment. Je comprends que sa mission est vitale et qu'il ne peut pas trahir son devoir, même pour toi.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, mon cher Charlie... J'attendrai Richard jusqu'à la Seconde Venue s'il le faut. Peut-être pourrais-je rester au-dessus de la taverne... Je ne peux pas continuer à profiter de l'hospitalité de John si longtemps.";
			link.l1 = "Arrêtez de dire des bêtises, madame ! Votre présence nous honore et je ne m'appelle pas Charlie le Knippel si je mets à la porte la fiancée de mon cher ami Richard Fleetwood !";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Je suis très touchée par ton attitude envers moi. Je ne suis qu'une simple fille et une juive en plus...";
			link.l1 = "Mademoiselle ! Je sais que c'est un discours insensé, vous êtes une jeune femme chrétienne de bonne foi ! Et ne songez même pas aux tavernes ! Je ne me pardonnerai jamais si je vous ai failli dans mon service à Richard.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Merci, Charlie. Je suis heureux que tu sois un... homme de bien.";
			link.l1 = "Il est de mon devoir, mademoiselle. Maintenant, je suis désolé, mais je dois y aller. Vous pouvez librement vous promener en ville maintenant, vous devez vous sentir assez seule confinée dans cette maison, n'est-ce pas ?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Eh bien... John est une compagnie très intéressante. Il peut parler de ses poudres, mélanges et diverses... maladies pendant des heures. C'est aussi un homme poli et courtois. Je vais également régulièrement à l'église, le prêtre local est assez aimable... mais, bien sûr, Richard me manque vraiment.";
			link.l1 = "Je pense qu'il sera bientôt de retour. Charlie le Knippel est à votre service au cas où vous auriez besoin de quoi que ce soit.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "J'ai entendu des rumeurs sur Richard... qu'il a disparu. Sais-tu quelque chose à ce sujet, Charlie?";
			link.l1 = "Je le sais, Abigail. Je suis désolé... Richard Fleetwood est parti pour l'Angleterre et il ne reviendra pas. Il a eu une promotion ou un transfert, quelque chose comme ça... de toute façon, après ce qu'il t'a fait, je ne veux plus entendre parler de lui.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, je savais que ça finirait ainsi....(sanglots) Pourquoi n'ai-je pas écouté papa ! Au moins, il aurait été content si j'avais épousé Lucas Rodenburg.";
			link.l1 = "Veuillez me pardonner encore, mademoiselle...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Pour quoi, Charlie ? Tu n'es pas coupable du tout. Tu n'as été que gentil avec moi !";
			link.l1 = "Pour moi vous annoncer encore plus de mauvaises nouvelles. Je viens juste de rentrer de Curaçao, Lucas Rodenburg a été arrêté pour sédition et trahison contre la République. Il est envoyé à Amsterdam enchaîné pour être jugé. Il a tenté d'assassiner Peter Stuyvesant, directeur de la Compagnie. En plus de cela, il a tenté de renverser le gouverneur de Willemstad et est soupçonné du meurtre d'au moins une autre personne, donc je doute que le Stathouder se contente de lui infliger une tape sur les doigts.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Oh Dieu ! Quel cauchemar ! Je pense que je vais m'évanouir ! Charles, est-ce vrai ? Non, je t'en prie, dis que ce n'est pas le cas !";
			link.l1 = "Désolé, mademoiselle, cela empire. Il a été révélé lors de l'enquête sur les actions de Rodenburg que le pirate qui avait coulé votre flûte agissait sous les ordres de Lucas Rodenburg. Il menait sa propre guerre privée contre la marine marchande anglaise. Je suis vraiment désolé, Abigail. Tous les hommes que vous avez rencontrés ici aux Caraïbes ont été des menteurs, des voleurs et des meurtriers.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh...Je suis perdu. Charles... s'il te plaît... ramène-moi chez moi à Willemstad. J'ai besoin de mon papa...";
			link.l1 = "Bien sûr, chère demoiselle. Malheureusement, il n'y a rien pour vous ici à St. John's. Allez, faites vos bagages, dites adieu à John et nous mettrons les voiles immédiatement.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Non, Charlie, je dois te remercier. Sans toi et John, je ne sais même pas ce qui me serait arrivé. Vous êtes les seuls hommes honnêtes que j'ai rencontrés dans l'archipel.";
			link.l1 = "Hm... tu me fais rougir, Abigail. J'étais heureux de t'aider. Et je suis vraiment désolé pour tout ce bazar.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Tu sais, Charlie, j'ai beaucoup réfléchi pendant notre voyage vers Curaçao. Tout est clair maintenant - Richard Fleetwood, Mynheer Rodenburg - tout semble être un horrible cauchemar qui a enfin pris fin. Je suis à nouveau avec mon père et nous pouvons revenir à une vie normale\nCe ne sera pas facile cependant - nous n'avons pas d'argent. Mais nous allons nous en sortir, tout ira bien. La Sainte Mère prendra soin de nous, elle n'oublie jamais ses enfants, même mon vieux père têtu qui renie Son Fils.";
			link.l1 = "Mademoiselle Abigail, je vais vous aider.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Aidez-nous ? Mais comment, Charlie ?";
			link.l1 = "Richard m'a raconté l'histoire de ton naufrage et de ton sauvetage. De plus, je sais que ton père a pu cacher ses biens sur une île non cartographiée. Je vais la trouver et ramener ton argent.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Ni moi, ni mon père ne sommes en mesure de te dire où se trouve cette maudite île... Nous ne sommes pas marins. De plus, j'étais terrifié pour ma vie pendant l'attaque, je ne me souviens de rien à part le sang et l'odeur de la mort.";
			link.l1 = "Abigail, essaie de te souvenir. S'il te plaît, n'importe quel détail peut m'aider, même les plus insignifiants. Peut-être que quelque chose s'est passé avant l'attaque ? À quoi ressemble cette île ?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "L'île... Ça ressemble à une île ? Une baie, des jungles. Rien ne m'a vraiment marqué. Oh, je me souviens ! Peut-être que cela vous aidera. Peu de temps avant l'attaque des pirates, nous avions rencontré un fluyt et salué son capitaine. Il a été invité sur notre navire et a dîné avec notre capitaine. Nous étions là aussi. Peut-être qu'il connaît cette île.";
			link.l1 = "C'est quelque chose ! Quels étaient les noms du flûte et de son capitaine ?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Je ne me souviens pas, Charlie. Vraiment pas...";
			link.l1 = "Essaie de te souvenir, Abi !";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Nous t'attendrons. Aide-moi Charlie le Knippel. Tu es notre seul espoir... Je prierai pour toi! Que Dieu te garde!";
			link.l1 = "Je suis en route. Adieu, Abi. Adieu, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Oh, cher... quel dommage. Nous espérions, mais... merci quand même, Charlie, d'avoir essayé de nous aider alors que personne d'autre ne l'aurait fait. Il semble que ce soit le destin que Dieu m'a réservé.";
			link.l1 = "Adieu, Abigail. J'espère que tu iras bien.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Est-ce... est-ce vrai ? As-tu vraiment rapporté notre argent perdu ? Oh, Charlie !";
			link.l1 = "Oui, c'est vrai. Je l'ai. Tenez, prenez-le. C'est tout à vous.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Comment puis-je te remercier ?! Comment ?!";
			link.l1 = "Je n'ai pas besoin de remerciements, Abi. C'est la moindre des choses que je puisse faire pour toi. Maintenant tu peux commencer une nouvelle vie sans aucun Rodenburg, Fleetwood, ou tout autre homme étrange essayant de profiter de toi. Je suis sûr que ton père peut trouver un moyen de faire fructifier cet argent... cela semble être un trait héréditaire.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, ne sois pas si effronté ! Tu as fait tant pour moi, pour moi et pour mon pauvre père. Eh bien, je me suis habituée à ta présence dans ma vie. J'ai prié sans relâche pour toi chaque jour, et je continuerai à prier pour toi et ton équipage à la Bienheureuse Mère chaque jour à venir ! Tu es notre ange gardien. Le Seigneur lui-même t'a envoyé à notre famille, crois-le ou non\nAvant que tu partes, je veux que tu saches que les portes de notre maison te seront toujours ouvertes à tout moment. Et... s'il te plaît, laisse-moi t'embrasser, mon cher Charlie...";
			link.l1 = "Eh bien... oui, bien sûr Abi...si tu insistes.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Que Dieu te bénisse, Charles. Rien n'a changé pour nous... Je mendie des miettes devant l'église.";
			link.l1 = "Restez forte, mademoiselle. Que Dieu soit avec vous.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, c'est toi ! Je suis si heureux de te voir ! S'il te plaît, assieds-toi ! Je vais préparer du café !";
			link.l1 = "Je suis heureux de te voir aussi, Abi. Et je suis content que tu te portes bien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ah, c'est donc ça?! Je t'ai accueilli comme mon hôte et tu as décidé de me voler?! Gardes!!!";
			link.l1 = "Ferme ta bouche, fille idiote.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
