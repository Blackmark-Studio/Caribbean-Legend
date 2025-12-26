// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Sizi dinliyorum, sorunuz nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu, üçüncü kez tekrar sormaya çalışmanız...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloninin işleriyle uğraşıyorum, sen ise hâlâ bir şeyler sormaya çalışıyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yer ve zaman uygun değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Martinique'de kârlı bir anlaşma yaptım ve şimdi Blueweld'e yelken açmayı planlıyorum. Koloninizden maun ve kahve almak istiyorum. Ayrıca, brig'im istediğim kadar yük taşıyamıyor, bu yüzden burada, tersanenizden bir fluyt satın almam gerekiyor. Bu konularda yardımınızı rica edebilir miyim?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Yardımım mı? Tüccarımız son derece dürüst bir adamdır, sizi kandırmaya çalışacağını sanmam. Flüt hakkında gemi kaptanıyla konuşun, bu konuda size yardımcı olacaktır. Yine de bir sorun yaşarsanız, mutlaka bana gelin. Kolonimizle ticari ilişkileri geliştirmekle ilgileniyorum ve size tam desteğimi vereceğim. Ayrıca bu akşam bir ziyafet düzenliyorum, Bridgetown'un en parlak isimleri orada olacak. Sizin de gelmenizi isterim, kaptan.";
			link.l1 = "Davetiniz için teşekkür ederim, fakat maalesef çok meşgulüm. Hoşça kalın ve yardımınız için tekrar teşekkürler!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
