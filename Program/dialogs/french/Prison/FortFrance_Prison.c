// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parle, j'écoute";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Officier, j'ai entendu dire qu'un homme nommé Folke Deluc se trouve dans votre prison. Y a-t-il quelque chose que je puisse faire pour le libérer ?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Officier, c'est encore moi à propos du prisonnier Folke Deluc. J'ai acheté les droits sur sa dette et je veux que cet homme soit libéré et remis à moi. Voici ses papiers de dette, jetez-y un œil.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Bon après-midi, officier. Je veux m'informer sur mon équipier...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Voici les papiers, maintenant libère mon homme.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, ce marin? Il avait emprunté une somme considérable à notre banquier, ne l'a pas remboursée et a même tenté de s'échapper. Mais il a été rapidement retrouvé. Depuis, il est en détention et il restera ici jusqu'à ce qu'il rembourse sa dette.";
			link.l1 = "Hm. Et comment fera-t-il cela tout en restant en prison ?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Je m'en moque, monsieur.";
			link.l1 = "Amusant... Et combien doit cette pauvre âme?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Je ne sais pas. Demandez au banquier et il vous donnera des détails.";
			link.l1 = "Je vois, merci pour vos informations, officier.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Hm. Ils ont tous raison. Veux-tu vraiment que je libère ce prisonnier ?";
			link.l1 = "Oui. J'ai besoin qu'il rembourse sa dette et je sais comment il peut le faire.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "D'accord, je n'ai aucune raison de vous refuser. Deluc sera amené ici bientôt. Mais je dois vous avertir que ce renard s'enfuira à la première occasion, alors ne vous faites pas d'illusions à son sujet.";
			link.l1 = "J'ai compris, officier. Et maintenant, je veux récupérer mon débiteur.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oui, bien sûr. Sergent ! Amenez le prisonnier ! Folke Deluc, il semble qu'il ait un nouveau maître maintenant !";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ha ! Je dis, les commérages sur votre mésaventure divertiront Saint-Pierre pendant longtemps. Mais ne le prenez pas personnellement, Capitaine. Vous êtes clairement la victime de la mauvaise fortune. Entrez et ne vous inquiétez pas : votre navigateur ne s'échappera pas de cette conversation, ha ha !";
			link.l1 = "Hilarant. Merci, officier.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Compris, Capitaine. Nous agirons en conséquence.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
