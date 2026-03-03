// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsun?","Ne bilmek istersiniz?"),"Ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Bu üçüncü kez bana sormaya çalışıyorsun...","Senden bıktım, defol git!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Üzgünüm, fikrimi değiştirdim.","Önemli değil, kusura bakmayın."),"Unuttum, kusura bakmayın...","Üçüncü seferde olacak galiba, ha? Affedersin...","Affedersin, affedersin! O zaman ben kendim çıkarım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Dinle - buradan Joachim Merriman adında bir adam geçti mi? Orta yaşlı, bıyıklı, keçi sakallı ve delici bakışlara sahip Portekizli bir señor. Belki bir koyda ya da fenerin yakınında karaya çıkmıştır? Ona benzeyen birini gördün mü?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "Hayır, onun gibi birini görmedim. Fark ederdim, evet.";
			link.l1 = "Anladım, ne yazık. Vaktinizi ayırdığınız için teşekkür ederim, aramaya devam edeceğim o zaman.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
