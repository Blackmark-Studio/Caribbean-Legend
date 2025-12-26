// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Biz de az önce bundan bahsediyorduk. Herhalde unuttunuz...","Bu üçüncü kez beni rahatsız ediyorsun artık...","Aynı şeyleri papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru ya, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Enrique Gonzales'ı arıyorum. Onu nasıl bulabileceğimi söyleyebilir misiniz?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "Herkes Señor Gonzales'i tanır! Evi liman idaresinin hemen yanında.";
			link.l1 = "Kaç yaşında?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Pek kesin konuşamam ama en az elli yaşında gibi görünüyor. O evde epey zamandır yaşıyor. Korsanlarla ilgili türlü türlü abartılı hikayeler anlatmayı sever, muhtemelen onları sadece rüyalarında görmüştür.";
			link.l1 = "Sanırım aradığım adam o. Teşekkür ederim, "+npchar.name+", bana çok yardımcı oldun!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
