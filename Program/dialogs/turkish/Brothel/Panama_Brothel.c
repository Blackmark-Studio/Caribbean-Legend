// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("genç adam","genç hanım")+"?","Ne istiyorsun, "+GetSexPhrase("yakışıklı","güzelim")+" Sor bakalım."),"Yine mi sorular?","Tee-hee, eğer sizin için de uygunsa - sorular...",""+GetSexPhrase("Hm, neden kendine bir güzellik seçmiyorsun? Senden şüphelenmeye başlıyorum...","Hm, neden kendin için bir güzellik seçmiyorsun? Korkarım burada hiç erkek yok, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, affedersiniz.","Aslında, boşver..."),"Ben... özür dilerim, şimdilik sorum yok.","Haklısınız, bu zaten üçüncü kez oldu. Affedin beni.","Belki bir dahaki sefere, hanımefendi.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
