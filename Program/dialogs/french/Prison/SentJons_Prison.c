// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parle, j'écoute";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Récemment, l'un des soldats de la ville a arrêté et détenu Charlie Knippel. Est-il toujours ici ?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "C'est exact, mais pourquoi me le demandez-vous ?";
			link.l1 = "La chose est, Charlie est un de mes officiers. J'aimerais savoir de quoi il est accusé. Les soldats qui l'ont pris ne m'ont rien dit."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "D'accord. Ce n'est pas un secret de Polichinelle. Malheureusement, même pour vous. C'est un secret d'État, monsieur.";
			link.l1 = "Donc, j'imagine qu'une caution n'est pas envisageable ?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Exactement. Je comprends que c'est désagréable de perdre un membre d'équipage précieux, mais ni vous ni moi ne pouvons rien y faire. Je suis vraiment désolé, Capitaine.";
			link.l1 = "Pas de caution, je vois. Que diriez-vous alors... d'une compensation ? Une généreuse, je pourrais ajouter. Pour vous et tous vos hommes, afin que personne ne soit laissé de côté."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Un pot-de-vin ? Audacieux de votre part, Capitaine, mais aucune somme d'argent ne nous sauvera de la colère de ceux qui apprendront que nous avons laissé partir Charlie.";
			link.l1 = "Peut-être... Mais puis-je au moins lui parler ?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Pourquoi pas ? Vous ne pouvez rien faire pour le sauver ou l'aider à s'évader, alors... allez-y. Il est dans l'une des cellules.";
			link.l1 = "Ha, et s'il me dit de quoi il est accusé et révèle ce secret d'État qui vous préoccupe tant, Officier ?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Je ne m'inquiète pas pour ça. Vous comprendrez pourquoi. Allez, parlez à votre ancien officier avant que je ne change d'avis.";
			link.l1 = "Merci."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", int(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Il n'y a pas besoin, Capitaine. Comme je l'ai dit, vous auriez été jeté dans la même cellule que ce fou de Charlie. Mais, d'abord, le Gouverneur a apprécié que vous n'ayez pas résisté à l'arrestation, et ensuite, il n'a pas été content de la récente visite de l'usurier, dont les cris ont failli briser les fenêtres du palais...";
			link.l1 = "Il a demandé mon arrestation ?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Il n'a pas demandé - il a exigé. Et Son Excellence n'aime pas qu'on lui exige quoi que ce soit. Par conséquent, cet usurier a été montré à la porte.";
			link.l1 = "Hilarant. Maintenant..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Maintenant je vous suggère de faire de même, Capitaine de Maure. Et ne posez pas de questions auxquelles vous n'obtiendrez pas de réponses.";
			link.l1 = "Je ne partirai pas d'ici sans Charlie Knippel."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "S'il vous plaît, monsieur, laissez-moi parler avec Charlie Knippel. Ou au moins découvrir ce que..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "Dans ce cas, rejoins-le. Pas dans une cellule, mais dans l'au-delà.";
			link.l1 = "Alors, il est mort..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Vous êtes diablement perspicace, Capitaine. Et j'espère que vous comprenez que je ne vous dirai ni qui l'a fait, ni pourquoi.";
			link.l1 = "Vraiment?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Exactement. Et maintenant, ne teste pas ma patience - avant que je n'ordonne qu'on te jette dans une cellule pour avoir tué un soldat anglais.";
			link.l1 = "Considérant que peu de gens sortent de vos cellules, je ne voudrais pas y finir. Je ne vous souhaiterai pas une bonne journée."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel ne parlera à personne. Sauf peut-être au Créateur...";
			link.l1 = "Il est mort ?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "La sentence a été exécutée. Je ne peux vous donner aucun détail. Et j'espère que vous n'insisterez pas - cela pourrait mal finir pour vous. Pas seulement avec une cellule. Suis-je clair, Capitaine de Mor?";
			link.l1 = "Plus que clair. Adieu."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
