// Абрахам Норман
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
		case "First time":
			dialog.text = "Avez-vous besoin de quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Que veux-tu, camarade ? Suis ton chemin, occupe-toi de tes affaires. Laisse-moi simplement tranquille.","Hé, hé, l'ami. Tu vas te promener ? Eh bien, continue ton chemin et laisse M. Abraham tranquille. Il se promène aussi. Il prend un bol d'air marin frais.","Bonjour, ami. Veux-tu bavarder ? Il y a juste un problème : je ne suis pas d'humeur à converser. Alors va chercher quelqu'un d'autre à importuner. Va te détendre à la taverne. Prends un peu de rhum...");
				link.l1 = "Écoute, Abraham, aurais-tu croisé récemment un homme nommé Miguel Dichoso sur l'Isla Tesoro ? C'est un gars assez connu par ici.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Que veux-tu, l'ami? Suis ton chemin, occupe-toi de tes affaires. Laisse-moi tranquille.","Hé, hé, l'ami. Tu fais une promenade ? Eh bien, continue de marcher et laisse M. Abraham tranquille. Il va se balader aussi. Il prend un souffle d'air frais de la mer.","Salut, l'ami. Tu veux papoter ? Y'a juste un problème : j'suis pas d'humeur à causer. Alors va embêter quelqu'un d'autre. Va te détendre à la taverne. Prends un peu de rhum..."),LinkRandPhrase("Hé, Matelot. Quoi, t'as la tête dure ou quoi ? Je pensais avoir été clair.","Mon vieux, va te reposer un peu. Tu sembles avoir du mal à entendre.","Hé, mon pote, quoi, t'es stupide ou quoi? Je te l'ai déjà pratiquement expliqué."),"Pote, ne me mets pas en colère. J'ai massacré tant de terriens à mon époque, un de plus ou de moins ne fait vraiment pas de différence.","D'accord, tu m'as mis en rogne. Maintenant, soit tu sors ton épée rouillée, soit tu cours aussi vite que tu peux. Je te recommande la deuxième option...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("D'accord, ami. Je ne vais pas te déranger.","Très bien, très bien. J'ai compris...","Ouh là, on dirait que tu es le tonnerre des mers ! D'accord, je m'en vais d'ici.","Quoi ?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Que veux-tu, l'ami? Suis ton chemin, occupe-toi de tes affaires. Laisse-moi simplement tranquille.","Hé, hé, l'ami. En promenade ? Eh bien, continue ta route et laisse M. Abraham tranquille. Il va aussi se promener. Il prend un bol d'air marin.","Bonjour, camarade. Tu veux bavarder ? Il y a juste un problème : je ne suis pas d'humeur à discuter. Alors va embêter quelqu'un d'autre. Va te détendre à la taverne. Prends du rhum...");
				link.l1 = "Ecoute, Abraham, es-tu tombé récemment sur un homme nommé Miguel Dichoso sur l'Isla Tesoro ? C'est un type assez connu par ici.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Pas un geste ! Je suis le gouverneur de cette île. Quoi, tu ne me crois pas ?!";
					link.l1 = "Bien sûr que je le connais ! Qui ne connaît pas le gouverneur d'Isla Tesoro...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, appelle-toi amiral tant que tu y es, j'achèterai ça sans hésiter !";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Au garde-à-vous ! Regardez - l'Amiral Barbarigo ! Ne reconnaissez-vous pas mon célèbre sabre de cavalerie ?";
					link.l1 = "Mes excuses, Monsieur l'Amiral ! Dorénavant, je serai plus attentif.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Ton sabre de cavalerie est bien connu. Dommage qu'il soit entre les mains d'un imbécile.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Comme vous pouvez le voir, je suis ici en exil. J'attends de plus amples nouvelles du général Monk. Je vous demande de ne pas divulguer mon identité royale cachée. Les espions de Cromwell ont de longues oreilles.";
					link.l1 = "Mais bien sûr, votre Majesté. Personne ne saura jamais que Charles II se cache aux Indes occidentales.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Eh bien, et moi je suis le Pape Innocent X alors.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Qu'est-il arrivé à toi, Blaze ? Je te cherche depuis deux jours. Tu as complètement oublié ton père Nicolas !";
					link.l1 = "Je n'ai pas de temps pour toi, père! Je suis débordé.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Vous vous trompez, monsieur. Mon nom est "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Ch-ch... Je suis Davy Jones. Dis-moi, as-tu peur de la mort ?";
					link.l1 = "Bien sûr que je le suis, M. Jones. Surtout après une gueule de bois.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Une mort est une tragédie, mille morts ne sont qu'une statistique.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Je suis pressé de terminer ma nouvelle pièce. Vous devez m'aider à finir la phrase 'Être ou ne pas être' ?!";
					link.l1 = "C'est la question ! Devons-nous endurer l'offense et passer à autre chose...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Un verre, bien sûr. Mais je ne serais pas surpris d'attraper une maladie dans un bordel !";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Que diable racontes-tu ? 'Tesoro' ?! Autant l'appeler les Bermudes ! Cette île s'appelle l'île Norman d'après moi et tu ne l'oublies pas ! Je vais devoir t'enseigner la géographie...";
			link.l1 = "Hein ! Que veux-tu dire ?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Tu as raison, Marin. Je suis vraiment l'amiral Barbarigo, mais ça reste strictement entre nous. Prépare-toi à marcher. Nous partons bientôt. Cela te sera utile.";
			link.l1 = "Je suis extrêmement reconnaissant !";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Nous verrons qui est le sot à présent. En garde!";
			link.l1 = "Es-tu sérieux ?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "Que vous avais-je dit ! Allez, buvez à ma santé.";
			link.l1 = "À la tienne, amiral !";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Je t'avais demandé de ne pas divulguer mon nom ! Maintenant, je vais devoir te faire disparaître comme un témoin dangereux...";
			link.l1 = "Oh, j'attendais cela avec impatience !";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Pardonnez-moi, Votre Grâce ! Je ne vous ai pas reconnu dans cet accoutrement. Veuillez accepter ce modeste cadeau d'un véritable catholique.";
			link.l1 = "La folie se manifeste...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Tout le monde m'attaque ! J'ai attrapé un espion qui ressemble à mon fils ! Je suis sûr que Thomas l'a envoyé pour me crever mon deuxième œil !";
			link.l1 = "Dégage, crétin !";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Tu es fatigué et tu n'as pas l'air en forme, fiston. Va te faire soigner.";
			link.l1 = "Merci !";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "N'aie pas peur, camarade. Tu vois, mourir n'est pas effrayant du tout...";
			link.l1 = "On dirait que tu ne plaisantes pas !";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Apparemment, tu n'as pas peur. Je le savais. C'est du courage !";
			link.l1 = "Tu es un drôle de vieil homme...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Tu es un piètre poète, Matelot. Se pourrait-il que ta lame soit plus agile que ta langue ?";
			link.l1 = "Caramba ! Ce sabre de cavalerie n'est pas une pacotille, voyons !";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Zut ! Les choses se passent plutôt bien pour toi ! Qu'en dis-tu pour ton imagination !";
			link.l1 = "Reviens encore.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, je te reconnais ! Ha-ha !";
			link.l1 = "Encore...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "D'accord, mon pote, notre conversation est finie. Va-t'en maintenant.";
			link.l1 = "Comme vous dites...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso ? Pourquoi as-tu besoin de lui, hein ?";
			link.l1 = "Eh bien, j'ai besoin de lui. J'ai juste besoin de lui. Alors, l'as-tu vu ?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Que veux-tu dire par pourquoi ai-je besoin de lui ? Miguel est mon vieux compagnon, un ami, pourrait-on dire. Il est censé...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Je veux qu'il m'amène un nouveau navire, tout comme il l'a fait une fois pour Shark Dodson.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso a tué un homme. C'est pourquoi je le cherche.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Tu as juste besoin de lui... Tu as beeeesoin de lui ! Tout ce qu'il te faut, c'est Miguel Dichoso ! Non, je ne l'ai pas vu. Je ne l'ai pas vu depuis longtemps. Il n'y a rien avec quoi je puisse t'aider, Marin.";
			link.l1 = "Hm... D'accord, au revoir.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Un ami, dites-vous... Il semble avoir cultivé tout un tas d'amis. Il est sur le point d'en avoir un de moins...";
			link.l1 = "Hé, vieux. Qu'est-ce qui ne va pas chez toi ?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Oui, Dichoso est un maître dans ces métiers, quoi qu'il en soit. Mais je ne sais pas où il se trouve. Il est passé par ici mais est reparti. Alors va voir Alexus, Matelot. Il te construira un merveilleux rafiot.";
			link.l1 = "Hm... Merci pour le tuyau, l'ami.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "Et qui donc Dichoso a-t-il zigouillé pour que tu te mettes à le chercher, hein, camarade ? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "Que veux-tu dire? Quel Sharp a-t-il tué exactement? Il y a beaucoup de Sharp, tu sais.";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "Ch-ch-ch... (regarde autour) Donc tu penses aussi que Blaze Sharp a été tué par Dichoso ?";
				link.l1 = "Oui. Je n'ai pas seulement des soupçons, mais des preuves solides. Des entrées dans son journal de bord...";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "Vas-y, petit marin...";
				link.l1 = "Que veux-tu dire ? Dis-m'en plus.";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "Ah...Eh bien. Il l'a tué et c'est tout ce qu'il y a à dire. Tu sais combien de tueurs traînent par ici ? Un homme sur deux ! Non, Marin. Je n'ai pas vu Dichoso depuis longtemps. Je ne peux pas t'aider avec quoi que ce soit.";
			link.l1 = "Pitié...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Calme-toi, l'ami. Comment t'appelles-tu, hein ? Cela m'a échappé la mémoire...";
			link.l1 = "Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Écoute, "+pchar.name+". Dichoso a tué le pauvre Blaze. Je l'ai vu de mes propres yeux, oui-oui. Mais ils ne me croient pas. Vous voyez, ils pensent que je suis fou. L'un des leurs, mais fou. Et j'étais le meilleur officier d'abordage dans l'équipage de Nicolas Sharp lui-même ! Des bons moments ! Mais finalement, j'ai perdu mes griffes, sabot et lentille et je me suis échoué.\nQuoi ? Ah, c'est ça ! Tout le monde pensait que Shark était à blâmer, mais ce n'était pas lui. Non-non-non. Il y avait une dent de requin, un talisman de Dodson mais c'est Dichoso qui l'a plantée là.\nIl a dû la voler à Shark quand ils naviguaient ensemble sur une frégate appelée Fortune. Je n'ai pas bien dormi ce jour-là et je suis sorti me promener. J'ai vu Dichoso se faufiler dans la résidence de Sharp, j'ai entendu quelqu'un crier puis gémir. Peu après, Dichoso est sorti de la résidence et ses mains étaient ensanglantées.\nIls ne m'ont pas cru, non-non. Parce qu'il n'y avait pas de Dichoso sur l'île ce jour-là, mais Shark y était. Et ils ont trouvé sa dent. Mais j'ai vu Dichoso, j'en suis sûr. Personne ne savait qu'il était là ce jour-là. 'Le Chanceux' est un homme très rusé et redoutable...";
			link.l1 = "Tu n'es pas le premier à appeler Dichoso 'le Chanceux'. Pourquoi donc? Est-ce son surnom?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Tu ne parles pas espagnol, gars ? 'Dichoso' signifie 'chanceux' dans la langue papiste. Miguel le Chanceux, Miguel le Chanceux. C'est ce que signifie son nom.";
			link.l1 = "Miguel le Chanceux ?... Hum. Cela me rappelle quelque chose. Hum. Cette phrase me semble si familière...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Eh bien, bien que son nom de famille soit Dichoso, je ne pense toujours pas qu'il soit espagnol. Non, non. Il n'est pas espagnol. Bien qu'il ressemble à un Espagnol.";
			link.l1 = "Alors, que pourrait-il être ? Anglais, Français ?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Ce n'est pas de cela que je parle, Matelot... Oh, pardonnez-moi, Capitaine. Oui, Dichoso babille en français de manière assez fabuleuse, pas pire que vous. Et en anglais aussi. Cependant, dans ses veines coule du sang indien. J'ai vu beaucoup de gens comme lui dans ma vie. Ce n’est pas évident à voir, mais c'est un métis. Je vous le garantis.";
			link.l1 = "Parle-t-il indien ?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Oh, diable sait. Peut-être qu'il le fait. Bien que, attends. Il le fait ! Il avait l'habitude de prononcer constamment des phrases étranges dans une langue bizarre et il faisait une tête de sage effrayant et gonflait ses joues en les prononçant. Par exemple, il disait quelque chose comme : cogito ergo sum ! Et puis il roulait des yeux et cherchait la réaction des marins. Ou il s'exclamait ainsi : aut Caesar, aut nihil ! Il lançait aussi plein d'autres choses. Je ne me souviens pas de tout ce qu'il disait.";
			link.l1 = "Ce n'est pas une langue indienne. C'est du latin. Latin... Latin?! Nom de Dieu!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Pourquoi es-tu si nerveux, gars? Pourquoi cries-tu? T'es-tu fait mordre par un serpent ou quoi? Où est-il allé?";
			link.l1 = "Pourquoi ne l'ai-je pas vu dès le début ! Tout était juste sous mon nez ! Latin ! Miguel... Miguel le Chanceux !!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Eh, l'ami. Cesse donc de brailler. Les gens nous regardent. Qu'est-ce qui te tracasse, Marin... pardon, Capitaine ?";
			link.l1 = "Je sais qui est vraiment Miguel Dichoso. Il n'est pas espagnol. Il est français! Oh, j'étais si aveugle!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Nah-uh, idiot. Il n'est pas français. C'est un sang-mêlé. Son papa blanc a fricoté avec une petite Indienne, une de ces Arawaks ou Miskitos des Caraïbes ou même une Itza, et c'est ainsi que le Saint Miguel Dichoso est venu sur cette Terre. Tu ne le vois pas, mais moi, oui. C'est écrit dans ses yeux...";
			link.l1 = "Laisse de côté la question de son origine pour le moment. Où est-il, Abraham ?! Était-il ici ?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Ch-ch... Oui, il était ici. Mais il est parti. Il n'est plus sur Isla Tesoro.";
			link.l1 = "Pourquoi est-il venu ici ? Quel genre de navire a-t-il ?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "Son navire est un galion. Un grand galion de guerre. Pourquoi il est venu ici... Eh bien, il reniflait en posant des questions. Mais j'ai entendu ses conversations, oui oui ! Il cherchait un certain Charles de Maure. Oui, c'est ça. Charles de Maure. Attends, c'est toi, Charles de Maure ! Il te cherchait, camarade.";
			link.l1 = "Sais-tu pourquoi ?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Eh bien, certainement pas pour visiter la taverne et siroter du rhum avec toi. Il voulait te capturer. Oui, oui! Te capturer! Tu es dans de beaux draps, capitaine!";
			link.l1 = "Je n'en doute pas...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "Et toi ? Pourquoi le cherches-tu ? Oh, je comprends, je comprends : pour le tuer ! Tue-le, tue ce salaud ! Venge Blaze Sharp ! Blaze était un type formidable. Je me souviens de lui, même enfant, il était comme Nicholas.";
			link.l1 = "Où est allé Dichoso ?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Il était en route pour Blueweld. Il a dit que Charles de Maure doit être recherché sous l'aile du Diable des Forêts. Mais il a laissé ses hommes ici... Attends. Je pense que tu as déjà été remarqué !";
			link.l1 = "Qui m'a remarqué ?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Les hommes de Dichoso. Il a ordonné de te surveiller ici. Oh, je sais, je sais ! Sois vigilant, capitaine : les récifs de l'Isla Tesoro sont entourés de navires et ils attendent là pour ta tête. Le capitaine est rusé comme un renard. Ne te laisse pas berner.";
			link.l1 = "Je vais essayer...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "Et une chose de plus : ici, prends mon épée de cavalerie. Prends-la, prends-la. Tu en auras besoin. C'est l'épée du Capitaine Barbarigo lui-même. C'est une lame excellente. La meilleure de l'archipel. Ne sois pas timide, prends-la. Blaze Sharp sera vengé !";
			link.l1 = "Merci, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Va maintenant. Va, tu es surveillé. Fais en sorte de paraître intelligent. Ou stupide. Peu importe. Sois juste prudent !";
			link.l1 = "Merci, l'ami. Tu n'imagines pas à quel point tu m'as aidé. Bonne chance !";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
