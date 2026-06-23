// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez.","Je vous écoute, quelle est votre question ?"),"C'est la seconde fois que vous essayez de demander...","C'est la troisième fois que vous essayez encore de demander...","Quand cela va-t-il finir ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous essayez encore de demander quelque chose !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Je veux voir le Chevalier de Poincy. C'est au sujet de la dette de mes frères.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Ah, eh bien, je suis informé de cette dette... Avez-vous la somme requise avec vous ?";
			if (int(pchar.money) >= 1000000)
			{
				link.l1 = "Bien sûr que j'en ai. Comment cela pourrait-il être autrement ?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Non, je n'ai pas encore autant d'argent.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Alors reviens quand tu auras et ne dérange pas le Chevalier.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Passez par la porte à droite alors. Le Chevalier vous recevra.";
			link.l1 = "Merci !";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
