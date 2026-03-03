// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce dükkânımdayken bana bir soru sormaya çalıştınız...","Bu bugün üçüncü kez soruluyor. Benim işim var, boş muhabbetlerle oyalanamam...","Daha fazla sorunuz mu var? Onun yerine bir anlaşma yapmaya ne dersiniz?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Evet, doğru. Denedim... Mağazadayken...","Evet, bu üçüncü soru...","Hm, belki bir anlaşma yapabiliriz...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
