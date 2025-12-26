// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Oficial, soube que um oficial do navio 'Cantavro' está sendo mantido aqui. Isso procede?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Voltei para perguntar sobre Don Lope de novo, oficial. Já recebeu a ordem de soltura dele?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "O oficial do 'Cantavro'? Don Lope Montoro? Sim, ele está detido aqui. O que você quer com isso?";
			link.l1 = "Gostaria de pedir permissão para visitá-lo.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "Com licença, mas com base em quê?";
			link.l1 = "É só uma questão pessoal. Eu o conhecia na Europa e fiquei chocado com a notícia da prisão dele, além dos boatos que se espalharam pela cidade. Gostaria de falar com ele.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Hm...";
			link.l1 = "Oficial, talvez eu possa... 'agradecer' por me deixar visitá-lo?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "Não há necessidade disso. Eu permito que você se encontre com Don Montoro. Os guardas vão deixar você passar.";
			link.l1 = "Obrigado!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "De fato, minhas ordens são entregar Don Lope Montoro diretamente ao comandante. Mas imagino que ele não vai sair da cela por algumas semanas. Você pode ir vê-lo enquanto ele ainda está aqui.";
			link.l1 = "Obrigado, oficial, é por isso que estou aqui.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
