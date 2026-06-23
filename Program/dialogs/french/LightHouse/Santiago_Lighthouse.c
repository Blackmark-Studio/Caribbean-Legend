// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que veux-tu ?","Que souhaitez-vous savoir ?"),"Que voulez-vous, "+GetAddress_Form(NPChar)+"?","C'est la troisième fois que tu essaies de me demander...","J'en ai assez de toi, va-t'en !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Désolé, j'ai changé d'avis.","Ce n'est rien, désolé."),"J'ai oublié, mes excuses...","La troisième fois est la bonne, hein ? Excusez-moi...","Désolé, désolé ! Je m'en vais alors...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Salutations. L'inquisiteur de Santiago, Dadre Vincento, vous a mentionné dans sa lettre. Il a dit que vous pourriez m'aider.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Des nouvelles de Padre Vincento, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "J'ai besoin de voir le Père Vincento. J'ai trouvé les objets qui l'intéressent.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Alors, "+npchar.name+", qu'est-ce que le Père Vincento vous a dit ?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Bien sûr, Señor. Vous devez être un homme de grande renommée si le Padre Vincento fait affaire avec vous.";
			link.l1 = "Splendide. Vous êtes donc notre messager. Maintenant écoutez, cet homme est d'un grand intérêt pour Padre Vincento. Il est maintenant sous votre responsabilité, vous devez le transférer à Santiago ou trouver quelqu'un qui le fera.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "... ";
			link.l1 = "Vous êtes responsable du prisonnier pour le compte de l'Inquisiteur. Je ne vous conseillerais pas de lui enlever ses chaînes, Gaius Marchais est un homme fort. Remettez cette lettre au père Vincento et dites-lui que j'attends une réponse de sa part dans deux jours. Cela devrait suffire, je l'espère.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Compris, Señor. Je ferai de mon mieux. Ce n'est pas la première fois que j'aide le saint père.";
			link.l1 = "Ce n'est pas tout. Le capitaine de la caraque, San Gregorio, Carlos Guevarra, doit être passé par ici. Il m'a apporté de la vanille. Vous a-t-il remis ma lettre ?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Oui, votre cargaison est en bon état et vous attend, Señor.";
			link.l1 = "Bien, je le ferai charger sur mon navire alors. Je serai ici pendant deux jours en attendant la réponse du Padre Vincento. Ce n'est pas un adieu pour l'instant, "+npchar.name+" !";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + int(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Oui, Señor. Voici une lettre de Padre Vincento. Il est très content de vous, le reste vous le découvrirez dans la lettre.";
			link.l1 = "Splendide. D'ici là, "+npchar.name+"Et pour l'instant - adieu.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Très bien. Donne-les-moi et je les apporterai au saint père.";
			link.l1 = "Aucun moyen, gars ! Ce n'était pas facile de les obtenir et je ne vais pas les céder comme ça. Je ne les donnerai qu'en personne au Padre Vincento.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Mais señor ! Comment puis-je savoir que vous ne me roulez pas ?";
			link.l1 = "Jette un oeil : l'encensoir, le calice et la croix avec le lazurite... "+npchar.name+", qui crois-tu que je suis ? Penses-tu vraiment que je sois assez stupide pour aller à l'Inquisition sans eux ?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Veuillez me pardonner, señor... Revenez demain et je parlerai de votre arrivée au Padre Vincento.";
			link.l1 = "Bien. À demain.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Son Excellence vous recevra, Señor. Ne tardez pas à lui rendre visite. Voici le document, montrez-le aux gardes et ils vous laisseront entrer. Mais hissez d'abord un pavillon espagnol ou les soldats risquent de vous arrêter.";
			link.l1 = "Compris. Espagnol alors. Merci, l'ami ! Je suis en route !";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
