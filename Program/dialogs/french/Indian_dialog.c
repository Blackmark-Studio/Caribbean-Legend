// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nous n'avons rien à discuter!";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Visage pâle","Squaw blanche")+" veut parler?","Vous encore, "+GetSexPhrase("Visage pâle","Squaw blanche")+".",""+GetSexPhrase("Visage pâle aime parler. Il ressemble à une squaw.","La squaw blanche aime parler.")+"","Les esprits ont amené mon visage pâle "+GetSexPhrase("frère","soeur")+" à moi.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oui.","Ouais, c'est encore moi.","Très poétique.","Je suis aussi heureux de te voir.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Dites, pourquoi êtes-vous venu, visage pâle?";
			link.l1 = "Oh, rien de particulier, je voulais juste écouter ce que tu avais à dire...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("L'homme blanc veut parler?","Vous encore, visage pâle?","Visagepâle aime parler.","Les esprits ont amené mon frère visage pâle à moi.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oui.","Oui, c'est moi encore.","Très poétique.","Je suis heureux de te voir aussi.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+"écoutez-vous, fils de la mer.","Que voulez-vous de "+npchar.name+", visage pâle?","Mes oreilles sont ouvertes à vos paroles, étranger.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("J'ai quelque chose pour toi. Tu veux y jeter un oeil?","Voulez-vous jeter un oeil à quelque chose de vraiment intéressant? Vous l'aimerez sûrement...","J'ai quelque chose qui te plaira, enfant de la jungle. Tu veux jeter un coup d'oeil?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, rien de particulier, je voulais juste écouter ce que tu avais à dire...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" veut regarder. Montre-le.",""+npchar.name+" est intéressé. Montre moi.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Donne un miroir.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Maintenant "+npchar.name+" peut se regarder non seulement dans l'eau de la rivière! Merci, gentil étranger!";
			link.l1 = "Certainement, maintenant tu peux admirer ton visage autant que tu le souhaites...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Si beau! Ce bracelet est pour "+npchar.name+"? Merci, aimable étranger !";
			link.l1 = "Mets-le sur ta main basanée, beauté, tu seras splendide...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Quelle belle bague? C'est pour "+npchar.name+", oui? Merci, gentil inconnu!";
			link.l1 = "Mettez-le à votre doigt, et tous vos amis seront jaloux...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Ces merveilleuses perles vertes sont pour "+npchar.name+"? Si beau! Merci, gentil inconnu!";
			link.l1 = "Pare ton cou avec eux, fille de la selva. Tout le monde t'admirera...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, quelle belle bague verte ! C'est un cadeau pour "+npchar.name+"! Merci, gentil inconnu !";
			link.l1 = "Ça sera magnifique sur ta main jolie dame...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Je voulais demander "+npchar.name+"quelque chose, fils de la mer?";
				link.l1 = "Tu as raison, jolie. Moi et mes guerriers intrepides allons à la selva, à l'établissement espagnol parmi les montagnes et nous cherchons un guide. Je serai généreux avec l'homme lui-même et aussi avec sa femme. J'ai beaucoup de richesses : de belles armes à feu, des lunettes magiques, des miroirs, des colliers, des bracelets et des bagues. Peut-être que ton mari peut être le guide que nous cherchons?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Salutations, fils de la mer. Moi, c'est Kumwana, chef du clan de la Tortue des peuples Locono. Quelle affaire t'amène à mon village?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Je vous ai apporté un cadeau, chef. Jetez un oeil, cela va vous plaire.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Chef, je suis venu demander votre aide. Je veux atteindre un établissement espagnol appelé Merida, il est situé parmi les montagnes dans votre selva, le problème est que je ne sais pas comment y arriver.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "C'est très bien pour toi, fils de la mer, de ne pas connaître le chemin là-bas. Il passe par une forêt, une terre de la tribu intrépide de Capong. De vrais jaguars, ils sont, oh-ey! Moi jamais aller à cet endroit espagnol. Mon peuple - peuple pacifique, nous n'allons pas au pays de Capong. Kumwana ne peut pas te donner de conseil. Route trop dangereuse.";
			link.l1 = "Mais les Espagnols ont trouvé un chemin ! Et je n'ai pas peur de ces Capongs...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Mais tu devrais. Ils sont des gens cruels. Ils ont tué beaucoup de mon peuple dans les bois. Kumwana a tout dit.";
			link.l1 = "Eh bien, merde...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Toi encore, fils de la mer. Que veux-tu dire à Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Je t'ai apporté un cadeau, chef. Regarde, tu vas l'aimer.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Un espoir de trouver Merida est toujours avec moi...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Les Locono sont toujours ravis de voir de bons amis.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Donne un pistolet en cadeau."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Donne une boussole.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Donne une longue-vue bon marché.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Donne une longue-vue commune."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Donne une bonne longue-vue."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Quelle jolie arme de visage pale! Kumwana accepte ton cadeau! Toi aussi, fils de la mer, accepte un cadeau de Kumwana et du peuple Locono.";
			link.l1 = "Gratitude, chef !..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Amulette magique des visages pâles! Kumwana accepte votre cadeau! Toi aussi, fils de la mer, accepte un cadeau de Kumwana et du peuple Locono.";
			link.l1 = "Gratitude, chef !..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey ! Tube magique des visages pâles ! Kumwana accepte votre cadeau ! Toi aussi, fils de la mer, accepte un cadeau de Kumwana et du peuple Locono.";
			link.l1 = "Gratitude, chef !..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey ! Tube magique des visages pales ! Kumwana accepte ton cadeau ! Toi aussi, fils de la mer, accepte un cadeau de Kumwana et du peuple Locono.";
			link.l1 = "Gratitude, chef !..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey ! Tube magique des visages pales ! Kumwana accepte ton cadeau ! Toi aussi, fils de la mer, accepte un cadeau de Kumwana et du peuple Locono.";
			link.l1 = "Gratitude, chef !..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Qu'est-ce qui t'amène dans notre village, fils de la mer?";
			link.l1 = "Chef, je suis venu demander votre aide. Je veux atteindre une colonie espagnole appelée Merida, elle est située parmi les montagnes dans votre selva, le problème est que je ne sais pas comment y arriver. Peut-être, pourriez-vous me fournir un guerrier courageux qui nous montrerait le chemin?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey ! Chemin dangereux, dangereux. Le chemin passe par une forêt, une terre de la tribu intrépide de Capong. De vrais jaguars, ils sont, oh-ey ! Je ne vais jamais à cet endroit espagnol. Mon peuple - peuple paisible, nous ne nous rendons pas sur la terre de Capong.";
			link.l1 = "Je dois vraiment me rendre à Merida. Kumwana, demande à tes hommes s'il te plaît, peut-être que quelqu'un acceptera de rejoindre mon unité ? Mes guerriers sont expérimentés, bien armés et ne craignent rien, pas même le Diable. Nous protégerons le guide et le récompenserons généreusement une fois que ce sera fini.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Très bien, fils de la mer. Je vais rassembler un cercle de guerriers et leur parler de tes souhaits. Rendez-vous demain après l'aube.";
			link.l1 = "Gratitude, chef !";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey ! Toi encore, fils de la mer. Que veux-tu dire à Kumwana ?";
			link.l1 = "Rien pour l'instant, chef.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Ecoute, Kumwana. Mon peuple et moi avons vraiment besoin de traverser la rivière et d'atteindre cette maudite petite ville. Laisse-moi te expliquer à quel point c'est crucial pour nous.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Mes chasseurs vous ont déjà informé que...";
			link.l1 = "Il n'y a pas besoin de te répéter deux fois, Kumwana. Mais regarde dehors - et ne surestime pas tes capacités. Mes vaillants gars qui sont venus ici pour des pierres espagnoles sont dispersés dans ton village. Et leur patience s'épuise. Et ce qui se passera quand elle sera finalement épuisée, il vaut mieux que tu ne le saches pas - crois-moi.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Ferme ta gueule et écoute, singe à la peau rouge. Mon peuple peut être bien plus terrible que ces maudits Kapongs. Ne te laisse pas tromper par le fait que nous sommes si gentils maintenant. Je te donne un choix simple : soit tu trouves un guide dans les vingt-quatre heures, soit nous vous ligoterons tous et vous enverrons à travers la jungle devant notre escouade. Si tu nous mènes dans la mauvaise direction, tu périras toi-même dans les marécages ou tu iras ligoté combattre les Kapongs. Compris ?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, j'ai besoin de ce guide. Nous avons fait un long chemin, et je ne veux vraiment pas dire à mes gars que c'était en vain.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana a déjà dit, aucun des Lokono ne veut aller avec le visage pâle.";
			link.l1 = "Et tu ne peux rien y faire ? Demande à quelqu'un personnellement. Ordonne, après tout. Tu es le chef ou pas ?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Le chef ne force pas l'Indien. Le chef dirige et veut la paix pour son peuple. Les Indiens savent - le Kapong verra que le Lokono apporte les visages pâles. Leurs têtes doivent être capturées par Kanaima. Ils viennent pour se venger du Lokono. Kapong - pour tuer. Capturez le Lokono, faites des esclaves.";
			link.l1 = "Et qui a capturé vos têtes? Quel esprit ou démon rend les Indiens de tels lâches ? Eh bien, peut-être que je vais vraiment devoir abandonner la campagne contre Merida. Mais souviens-toi de quelque chose, chef. Chaque fois qu'on me demande ce que je sais des Lokono, je répondrai invariablement - qu'ils sont une tribu de lâches sans valeur. Dirigés par un chef aussi lâche et myope qu'eux, dont le visage est déformé par une grimace d'horreur à la simple mémoire des Kapongs. Tu ne gagneras pas la gloire parmi les Indiens, ni le respect parmi nous, les visages pâles.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Visage pâle ne connaît pas les coutumes des Indiens...";
			link.l1 = "Je sais assez pour savoir qui les Indiens appellent un lâche et qui un guerrier courageux. Adieu, Kumwana. Et souviens-toi de mes paroles. Tu es un dirigeant lâche et myope.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Pourquoi me menaces-tu ainsi? Nous pensons que tu es bon...";
			link.l1 = "Je suis bien, tant que tu coopères, compris? Tu as un jour. Et crois-moi, mes gens feront tout ce que j'ordonne. Nous sommes plus forts. Et si tu en doutes... J'ai vu ta femme. Et tes filles. Je pense que tu as compris le message maintenant.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Pourquoi me menaces-tu ainsi? Nous pensons que tu es bon...";
			link.l1 = "Je suis gentil, tant que tu coopères, compris ? Tu as une journée. Et crois-moi, mes gens feront tout ce que j'ordonne. Nous sommes plus forts. Et si tu en doutes... J'ai vu ta femme. Et tes filles. Je pense que tu as reçu le message maintenant.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana comprend, visage pâle. Dans le village, il y a un chasseur nommé Tagofa. Peut-être peut-il vous guider vers la colonie...";
			link.l1 = "Je reviendrai dans vingt-quatre heures. Charlie Prince n'a rien de plus à ajouter, sauvage.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Fils de la mer, c'est toi. Kumwana a parlé avec les guerriers du Locono.";
			link.l1 = "Et alors? Avez-vous un volontaire?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Nous avons quelques chasseurs qui y ont été. Mais ils craignent les Capongs, les jaguars sont sur le sentier de la guerre. Ils ne vont pas, ils disent que Capong tue votre unité. Ils ne craignent pas les visages pâles.";
			link.l1 = "Mes guerriers sont bien meilleurs que n'importe lesquels d'entre eux ! Une partie de mon unité a passé une vie entière dans la jungle ! Nous ne sommes pas des amateurs !";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Je suis désolé, fils de la mer. Mes chasseurs ont peur, les Capongs sont dangereux, très très.";
			link.l1 = "D'accord, alors peut-être, peuvent-ils expliquer comment s'y rendre ? En détails.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Pour y arriver, tu devrais naviguer sur la rivière puis débarquer à l'endroit spécial. Si c'est le mauvais endroit, tu te retrouveras dans le marais et tu mourras. Notre selva est pleine de dangers. Tu ne trouveras pas l'endroit par toi-même, fils de la mer.";
			link.l1 = RandSwear()+"Et que devrais-je faire alors ? Comment persuader vos chasseurs ?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana ne dit plus rien, fils de la mer.";
			link.l1 = "D'accord...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Mon mari Tagofa est le meilleur chasseur de la tribu. Oh-ey! "+npchar.name+" est fière de son mari. "+npchar.name+" souvent part avec Tagofa à Selva. Va loin. Tagofa sait où se trouve la colonie espagnole.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Tagofa connait-il le chemin vers la ville espagnole que les visages pâles appellent Merida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Eh bien, eh bien... Tagofa sait-il comment se rendre à la ville espagnole?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mon mari ne va pas dans la jungle, fils de la mer. Il pêche. Bon pêcheur, oh-ey! ","Mon mari bon chasseur, oh-ey, mais il ne va pas dans la jungle profonde."),RandPhraseSimple("Un jaguar a blessé mon mari à la chasse. Maintenant, il reste au village, fabrique des flèches, oh-ey !","Il y a six lunes, trois Capongs ont attaqué mon mari. Maintenant, il ne va plus chasser loin du village. Jamais ! oh-ey !"));
				link.l1 = LinkRandPhrase("Dommage...","Dommage...","Quel dommage..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa a grandi dans cette jungle. Il connaît chaque arbre et chaque pierre autour !";
			link.l1 = "Je vous donnerai à vous et à Tagofa de nombreux cadeaux s'il nous y emmène. Bijoux, armes, n'importe quoi. Tout ce que vous voulez. Dans la limite du raisonnable, bien sûr, he-he. Comment puis-je parler à votre mari?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa n'ira pas avec le visage pâle. Tagofa restera dans le village. Aller à la chasse. Ne vous battez pas avec le Kapong.";
			link.l1 = "Il n'aura pas à se battre avec les Kapong. Dès qu'il les verra, il pourra se cacher. Seul mon peuple se battra.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Non, yalanaui. Le visage pâle ne tient jamais sa parole. Le visage pâle parle - et le mot s'envole immédiatement dans le vide. Le Kapong tuera Tagofa puis viendra dans notre village, tuera le Lokono.";
			link.l1 = "Penses-tu que ces Kapongs sont tout ce dont tu dois t'inquiéter ? Tu te trompes grandement...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu pour entrer dans le visage pâle ! Hayami ne parle plus à yalanaui.";
			link.l1 = "Eh bien, eh bien...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa est parti à la chasse il y a un jour. Il a promis de revenir demain quand le soleil dort. Viens demain, fils de la mer, je serai avec Tagofa dans cette cabane, en entrant dans le village, tourne à droite. Je lui demanderai s'il part ou ne part pas avec toi.";
			link.l1 = "Dites à Tagofa que je lui offrirai le plus joli pistolet. Et toi, je te ferai cadeau de beaucoup de bijoux.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono ne fait pas confiance aux Yalanaui. Yalanaui trompe l'Indien, fait de l'Indien un esclave. Mais Lokono entend ton nom, visage pâle. Ma confiance est tienne. Viens demain après le coucher du soleil, fils de la mer. Je serai avec Tagofa dans cette cabane. Je lui demanderai s'il ira avec toi ou non.";
			link.l1 = "Dites à Tagofa que je lui donnerai mon pistolet le plus beau. Et pour vous j'ai beaucoup de bijoux.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey !";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" est heureux de voir un fils de la mer. Tagofa est revenu. Mais il a trop bu de kasheeri et dort. Ne le réveille pas, Tagofa se repose. Je parlerai.";
			link.l1 = "Très bien, "+npchar.name+". Votre mari nous guidera-t-il à Merida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa a accepté de guider vos guerriers à travers la selva jusqu'au village espagnol. Mais il y a des conditions...";
			link.l1 = "Lesquels sont?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Vous protégez Tagofa des guerriers Capong. Tagofa ne se bat pas, ni contre les Espagnols, ni contre les Capong. S'il est en danger, il s'enfuira et personne ne le retrouvera, il est le meilleur chasseur Locono.";
			link.l1 = "Je vois. Vous vous inquiétez pour votre homme, cela est compréhensible. Je vous promets que nous allons nous occuper de tous ces Capongs par nous-mêmes.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa veut des cadeaux du fils de la mer : un petit pour tirer beaucoup de pierres et un grand pour tirer une pierre, les jolies. Il veut aussi des balles pour chaque pistolet : autant que les doigts des deux mains trois fois.";
			link.l1 = "Whoa ! Votre homme s'y connait en canons, hein ? Très bien. Quoi d'autre ?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Et Tagofa veut un bel oeil magique de visages pales.";
			link.l1 = "Une longue-vue ? Bien. Quelque chose d'autre ?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Plus rien pour Tagofa. "+npchar.name+" veut de belles choses. Bague en or avec une grande pierre rouge, et des perles de beaucoup beaucoup de pierres vertes. "+npchar.name+" l'a vu sur la blanche Mary à Maracaibo.";
			link.l1 = "Une bague en or avec des perles de rubis et de jade?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Pas de jade. C'est brillant et les hommes blancs le valorisent.";
			link.l1 = "Emeraude? Des perles d'emeraude?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey !";
			link.l1 = "Heh, "+npchar.name+" connaît quelque chose sur les bijoux ! Très bien, tu l'auras.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Apporte toutes les choses à "+npchar.name+" ensemble, fils de la mer. Puis Tagofa vous guidera, toi et tes guerriers. Ne perds pas de temps, dans une demi-lune Tagofa et moi irons au village voisin. Pour un grand jour. Maintenant vas, "+npchar.name+" veut dormir.";
			link.l1 = "Je ne vais pas vous faire attendre trop longtemps. à bientôt.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Tu as apporté quoi "+npchar.name+" et Tagofa a demandé?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Oui. Tout est conforme à votre liste.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Non, je suis toujours dessus.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" est heureux, fils de la mer. Je l'appelle maintenant mari. Il part avec toi. Mais souviens-toi de ce que tu as promis de "+npchar.name+"!";
			link.l1 = "Oui-oui, je me souviens de tout. Je le garderai en sécurité, ne vous inquiétez pas.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Mettez votre arme de côté, visage pâle, ou nous vous forcerons à le faire!";
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Ne t'inquiète pas, je le range...");
			link.l1.go = "exit";
		break;  

	}
}
