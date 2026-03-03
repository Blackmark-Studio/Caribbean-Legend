// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kaleniz hakkında ne düşünüyorsunuz? Güzel görünüyor, değil mi? Garnizonumuz da en az onun kadar iyi, ha...","Bir kale askerinin hayatı oldukça sıkıcıdır... Nöbet tutmak, devriye gezmek, uyumak ve dinlenmek, sonra yine aynısı baştan. Ama şehirde işler farklı... Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Askere saçma sorular sormak hoş karşılanmaz, "+GetAddress_Form(NPChar)+"...","Bugün üçüncü kez bana bunu sormaya çalışıyorsun...","Asker olmak kolay değil, ama işte yine buradasın"+GetSexPhrase(", seni ahmak,  "," ")+" beni sinirlendirmeye çalışıyorsun. Dikkat et, yoksa kendini kalenin zindanında bulursun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, rahatsız ettiğim için üzgünüm.","Söyleyecek bir şeyim yok, kusura bakmayın."),"Haklısınız, özür dilerim.","Haklısınız, bu zaten üçüncü sefer. Affedin beni.","Üzgünüm, önemli bir şey değil.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
