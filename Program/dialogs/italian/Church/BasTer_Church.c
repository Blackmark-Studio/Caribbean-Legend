// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Fai pure, sto ascoltando..."),"Sto ascoltando, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi quello di cui hai bisogno.","Un religioso ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, le mie scuse.","Chiederò, ma più tardi. Perdonami, padre.","Perdonami, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Vengo da voi riguardo a un fatto insolito, santo padre. Un corsaro di nome Guy Marchais ha presentato un oggetto molto prezioso alla vostra parrocchia non molto tempo fa. Era una croce pettorale d'oro con incastonato del lazurite. È vero?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh sì, mio figlio! È il miglior oggetto della nostra parrocchia. Non ho mai visto tale magnificenza in tutta la mia vita! Ma perché chiedi, mio figlio? Perché sei interessato a questa croce?";
			link.l1 = "Santo padre, so che ciò non sarà di tuo gradimento, ma questa croce è stata rubata da un'altra parrocchia e il religioso è stato assassinato durante l'atto. Quell'uomo che ti ha presentato questo oggetto è un assassino.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Tutti pecciamo, mio figlio, e accusare di aver ucciso un prete è una cosa seria. Hai delle prove? Da quale parrocchia è stata rubata questa croce?";
			link.l1 = "La mia parola non è prova sufficiente? Questa croce è stata rubata dalla parrocchia di Santiago e deve essere restituita.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago? Non è quella una città spagnola? Mio figlio, mi stai sorprendendo...";
			link.l1 = "Santo padre, tutti sono uguali davanti a Dio. Gli spagnoli sono cristiani proprio come noi e le divergenze tra le nazioni non devono applicarsi ai sentimenti dei credenti. Ti prego di restituire questa croce alla parrocchia di Santiago.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Mio figlio, non capisci che questa croce è un dono dei cristiani amanti per la nostra parrocchia?! No, mio figlio, non posso fare quello che chiedi.";
			link.l1 = "Non ti importa che il sangue sia stato versato su questa croce? Il sangue di un ecclesiastico, spagnolo o no, non importa.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Mio figlio, non hai mostrato alcuna prova e non posso prendere ciecamente la tua parola per buona. La croce rimarrà nella nostra parrocchia. Questa è la mia decisione finale. Inoltre, il tuo sforzo nell'aiutare gli spagnoli in questo caso mi preoccupa molto.";
			link.l1 = "Così sia, addio allora, santo padre...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
