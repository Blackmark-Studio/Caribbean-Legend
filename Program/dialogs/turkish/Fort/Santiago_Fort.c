// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kaleniz hakkında ne düşünüyorsunuz? Fena durmuyor, değil mi? Garnizon da hiç fena sayılmaz, ha...","Bir kale askerinin hayatı oldukça sıkıcıdır... Nöbet tutmak ve devriye gezmek, uyumak ve dinlenmek, sonra yine aynısı baştan. Ama şehirde işler farklı... Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bir askeri aptalca sorularla rahatsız etmek hoş karşılanmaz, "+GetAddress_Form(NPChar)+"...","Bugün üçüncü kez bana sormaya çalışıyorsun...","Asker olmak kolay değil, ama işte yine buradasın"+GetSexPhrase(", seni ahmak,  "," ")+" beni sinirlendirmeye çalışıyorsun. Dikkat et, yoksa kendini kalenin zindanında bulursun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, rahatsız ettiğim için kusura bakmayın.","Söyleyecek bir şeyim yok, kusura bakmayın."),"Haklısınız, özür dilerim.","Haklısınız, bu zaten üçüncü sefer oldu. Affedin beni.","Üzgünüm, önemli bir şey değil.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
