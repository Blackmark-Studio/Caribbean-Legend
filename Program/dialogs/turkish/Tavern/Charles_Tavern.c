// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bütün gün boyunca, bu soruyu üçüncü kez gündeme getiriyorsun...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Valet lakaplı bir adamı arıyorum. Onu tanıyor musun?";
				link.l1.go = "valet_1";
				link.l2 = "'Marlin' adında bir polacrenin kaptanını arıyorum. Onu nerede bulabileceğimi söyleyebilir misiniz?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("Hayır, bilmiyorum. Yani sana yardımcı olabileceğim bir şey yok.","Sana zaten bilmiyorum dedim!","Sarhoş musun yoksa sadece dalga mı geçiyorsun?","Beni rahat bırak!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Anladım. Ne yazık...","Ne yazık. Hatırlarsın sanmıştım...","Ayıkım! Sadece inatçıyım...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("Ah, Bay David Fackman! Tersanenin yakınında bir ev kiralıyor. Onu orada bulabilirsin.","Sana zaten cevap verdim. Beni dinliyor muydun gerçekten?","Sarhoş musun yoksa sadece dalga mı geçiyorsun?","Beni rahat bırak!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Teşekkürler!","Evet. Üzgünüm.","Ayığım! Sadece inatçıyım...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
