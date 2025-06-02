// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parlez, je vous écoute.";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "J'ai entendu parler d'une bande de voleurs et de brigands opérant dans les environs de Belize et dans la ville elle-même.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Je peux vous donner des informations sur le gang.";
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Quelles nouvelles de la bande ? Les avez-vous saisis dans la grotte ?";
				link.l1.go = "caleuche_7";
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Tout le village semble célébrer la capture d'un pirate. Pouvez-vous m'en dire plus à ce sujet ?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Volontiers ! Ce n'est pas n'importe quel pirate - c'est ce gredin de Matthew Lutter.";
			link.l1 = "La chance de chacun finit par s'épuiser.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Tu n'es pas Anglais, et tu n'as pas l'air d'un marchand, donc je comprends pourquoi tu n'es pas aussi excité. Lutter a terrorisé ces eaux pendant des années, attaquant à la fois nous et les Dons, mais plus souvent nous. Il a toujours réussi à échapper à nos patrouilles côtières, naviguant sur sa corvette, la Mouette, qui fut autrefois le navire le plus rapide de l'Archipel. Comment il est venu à commander un navire de guerre comme celui-là, seul Dieu le sait.";
			link.l1 = "Alors c'est vrai qu'il a perdu contre un marchand ? Sur une corvette ? Ça semble incroyable.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Aussi étrange que cela puisse paraître, c'est vrai. Un marchand, et un Espagnol en plus ! Notre marine pourrait apprendre une chose ou deux de lui. Le capitaine Sotta, réalisant qu'il n'y avait pas d'échappatoire, se prépara à la bataille...";
			link.l1 = "Un drôle de personnage, ce Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Peut-être. Il avait fait réaménager son navire pour transporter autant de cargaison que possible, rendant ainsi la fuite impossible. Sachant que les pirates en voulaient à sa cargaison, il a fait semblant d'être à la dérive. Et puis...";
			link.l1 = "...a-t-il hissé les voiles au bon moment ?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha ! Non, il a tiré une bordée de mitraille à bout portant alors que Lutter s'approchait, puis il est monté à l'abordage du pirate lui-même ! Quand il a découvert qui était Lutter, il nous l'a remis. Un véritable héros, un homme d'honneur !";
			link.l1 = "Ce n'était pas seulement l'honneur qui le motivait - il devait y avoir une récompense pour attraper le Fanfarond.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Parfois, le profit s'aligne avec de bonnes intentions. Mais oui, il a été généreusement récompensé. Sa Grâce l'a chargé de marchandises coûteuses en signe de gratitude de notre ville avant qu'il ne mette les voiles.";
			link.l1 = "J'aurais aimé le rencontrer - j'aimerais lui serrer la main. Dis-moi...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Votre informateur disait la vérité. Ces bandits sont devenus un vrai casse-tête pour nous. Voulez-vous nous en dire plus à leur sujet ?";
			link.l1 = "À part qu'ils m'ont volé une chose importante - rien vraiment. J'espérais que vous pourriez me dire quelque chose à leur sujet. Peut-être que l'un d'eux a été attrapé et qu'il est maintenant prêt à témoigner...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Je suis désolé de vous décevoir, capitaine, mais je n'ai aucune information à leur sujet. Je sais seulement qu'ils se cachent quelque part dans la jungle et qu'ils ont des complices en ville, c'est tout. Maintenant, si vous apprenez quelque chose de nouveau à leur sujet, veuillez me le dire immédiatement.";
			link.l1 = "D'accord, officier. Je ferai cela.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Es-tu sérieux, capitaine ? Parle, je suis tout ouïe.";
			link.l1 = "J'ai trouvé un de leurs informateurs en ville. Il m'a dit que leur bande se prépare à attaquer un navire, qui est censé arriver à la crique de Chetumal. Les scélérats se rassemblent "+sTime+"  la nuit près d'une grotte non loin de Belize. Pour y arriver, il suffit de prendre le chemin de gauche à la bifurcation dans la jungle.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "À la grotte ? Excellente nouvelle. Je vais ordonner de préparer une embuscade pour ces scélérats. Si vous avez bien compris et que votre informateur disait la vérité, nous attraperons ces salauds, et alors je solliciterai le gouverneur pour vous récompenser.";
			link.l1 = "Merci ! Je viendrai te voir quand ce sera fini.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "D'accord. Ça va.";
			link.l1 = "À bientôt, officier.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = hrand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Nous avons préparé un accueil chaleureux pour ces canailles, ha-ha-ha ! Si seulement vous aviez vu leurs têtes ! Nous les avons tous capturés, y compris le meneur ! Certains ont tenté de résister, mais ils ont été éliminés par nos vaillants soldats.";
				link.l1 = "Excellente nouvelle, officier ! Maintenant, les citoyens de Belize peuvent enfin dormir tranquilles.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... Mes soldats les ont attendus à la grotte toute la nuit, mais personne n'est jamais venu. Le sergent était vraiment furieux. C'est bien qu'il ne t'ait pas encore attrapé.";
				link.l1 = "Merde! Cela ne se peut pas! Dans quelle caverne as-tu tendu l'embuscade? Il y en a deux!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Où vous m'avez dit. À celui de droite à la fourche...";
			link.l1 = "C'EST CELUI DE GAUCHE ! À gauche de la bifurcation, imbéciles !";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Mais je me souviens parfaitement que vous avez dit 'à droite'.";
			link.l1 = "Oh mon Seigneur ! À gauche ! J'ai dit, À ! GAUCHE ! Vous les avez laissés filer, et c'était de votre faute !";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Alors tu as dû marmonner quelque chose dans ta barbe. Je peux entendre très bien, tu sais.";
			link.l1 = "D'accord, officier, je ne vais pas discuter. Je voulais vous aider, mais on ne peut pas aider ceux qui ne peuvent s'aider eux-mêmes. Adieu.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "J'ai rapporté au gouverneur votre rôle dans l'élimination de la bande. Il a grandement apprécié votre contribution et m'a autorisé à vous remettre une récompense : une prime monétaire et une arquebuse trophée.";
			link.l1 = "Merci !";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Merci pour le service, capitaine ! Si seulement tous nos citoyens étaient aussi consciencieux que vous, nous aurions vaincu le crime une bonne fois pour toutes il y a longtemps ! Bonne chance à vous !";
			link.l1 = "Adieu, officier ! Bonne chance à vous dans votre service !";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
