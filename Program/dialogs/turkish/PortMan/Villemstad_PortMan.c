// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, bu üçüncü sefer...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Köle isyanından sonra kaybolan barque hakkında bilgi almak istiyorum.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Toff Keller adında bir kaptanı bulmak istiyorum. 'Leiden' adında bir fluyt gemisi var. Bana sık sık Willemstad'a uğradığı söylendi, bu yüzden bana yardım etmen zor olmayacaktır.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... Neden ilgileniyorsun? Zenciler senin özel ilgi alanın mı?";
				link.l1 = "Mathias Beck, valinin emriyle buradayım. Kaçan zencilerin o gemiyi çalıp kaçtıklarından şüphelenmem için her türlü sebebim var. Bu yüzden aramalarımda bana her şekilde yardımcı olmanızı istiyorum.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Anladım. Sana yardımcı olamam. Barque '"+pchar.questTemp.Slavetrader.ShipName+"' sabaha kadar kaybolmuştu, kimse hiçbir şey görmemiş. Ben evde uyuyordum. Rıhtım bekçisi de ortadan kayboldu, arkasında hiçbir iz bırakmadan.\nVali, izler henüz tazeyken peşine düşmek için bir şalopa gönderdi ama elleri boş döndüler. Ne zencilerden ne de '"+pchar.questTemp.Slavetrader.ShipName+"'. Açıkçası, şalopa onları pek de dikkatlice aramadı, herkes hâlâ panik içindeydi ve kafirlerin ormandan çatal ve pala ile fırlayıp beyaz kanı için çıldıracaklarını sanıyordu.";
				link.l1 = "Bu pek yardımcı olmadı, ama yine de teşekkürler. Hoşça kal.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "Toff Keller mı? Tabii, onu tanırım! Düzenli olarak Trinidad’daki San Jose’ye ve Cumana’ya gider. Yakın zamanda Trinidad’a gitmişti. Sanırım onu orada bulabilirsin.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
