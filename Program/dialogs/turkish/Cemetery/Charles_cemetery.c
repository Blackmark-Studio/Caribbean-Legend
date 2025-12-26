// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Size nasıl yardımcı olabilirim?","Sana nasıl yardımcı olabilirim?"),"Söyle bakalım, seni ne üzüyor? "+GetAddress_Form(NPChar)+"?","Üçüncü kez, "+GetAddress_Form(NPChar)+", ne istiyorsun?","Senden bıktım. Defol!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, kusura bakmayın.","Önemli değil, affedersiniz."),"Beni affedin, önemli bir şey değil.","Haklısınız, bu zaten üçüncü sefer. Affedin beni...","Affedersiniz.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
