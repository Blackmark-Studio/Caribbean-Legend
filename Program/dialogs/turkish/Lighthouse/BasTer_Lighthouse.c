// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsun?","Ne bilmek istersiniz?"),"Ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Bu üçüncü kez bana sormaya çalışıyorsun...","Senden bıktım, defol git!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Üzgünüm, fikrimi değiştirdim.","Önemli değil, özür dilerim."),"Unuttum, kusura bakmayın...","Üçüncü seferde olacak galiba, ha? Affedersin...","Affedersin, affedersin! O zaman ben kendim çıkayım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
