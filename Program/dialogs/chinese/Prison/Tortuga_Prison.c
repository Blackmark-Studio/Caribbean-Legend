// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
        break;
        
        case "tonzag_bail":
            NextDiag.TempNode = "First_officer";
        
            dialog.text = "船长, 你到 托尔图加 的目的是什么? ";
            link.l1 = "我求你了! 帮帮我的同伴, 我会回答你所有问题! ";
            link.l1.go = "tonzag_bail_a";
            link.l2 = "你这么重要的人物, 在整个监狱都听到枪声之后, 居然不带任何护卫就到这里来了? ! ";
            link.l2.go = "tonzag_bail_b";
        break;
        
        case "tonzag_bail_a":
            dialog.text = "你拖延时间不回答, 他可正在流血。 我重复一遍问题。 ";
            link.l1 = "";
            link.l1.go = "tonzag_bail_1";
        break;
        
        case "tonzag_bail_b":
            dialog.text = "所发生的事情我已经知道得够多了。 我重复一遍问题。 ";
            link.l1 = "";
            link.l1.go = "tonzag_bail_1";
        break;
        
        case "tonzag_bail_1":
            dialog.text = "最后一次机会, 船长。 ";
            link.l1 = "我在执行总督大人交给我的任务! ";
            link.l1.go = "tonzag_bail_truth";
            link.l2 = "你很清楚, 我是一艘船的船长, 靠契约做事。 而且我每年都会来你们这个可爱的小岛几次! ";
            link.l2.go = "tonzag_bail_lies";
        break;
        
        case "tonzag_bail_truth":
            dialog.text = "我之前就有怀疑, 但并不完全确定。 你很幸运, 就在几天前, 卡普斯特维尔召开了一个重要会议。 一些非常有影响力的人达成了协议。 因此, 你不再是我的敌人了。 ";
            link.l1 = "你会帮助我们吗? ";
            link.l1.go = "tonzag_bail_truth_1";
			
            AddDialogExitQuestFunction("Tonzag_GetOut");
        break;
        
        case "tonzag_bail_truth_1":
            dialog.text = "我马上释放你。 你的同伴会被转移到船上接受治疗。 ";
            link.l1 = "谢谢你... ";
            link.l1.go = "tonzag_bail_truth_2";
        break;
        
        case "tonzag_bail_truth_2":
            dialog.text = "你差点就陷入困境了, 查尔斯! 离开这里, 至少一个月内不要返回 托尔图加。 让事情尘埃落定, 让人们冷静下来。 ";
            link.l1 = "我会的。 再见! ";
            link.l1.go = "exit";
            link.l2 = "你就一点都不解释吗? 哪怕一点点? ... ";
            link.l2.go = "tonzag_bail_truth_3";
        break;
        
        case "tonzag_bail_truth_3":
            dialog.text = "有人举报了你。 据称, 你是一个狂热的天主教徒, 来到我们这个美丽的小岛是为了恶意杀害可敬的总督。 ";
            link.l1 = "我不是狂热分子! ";
            link.l1.go = "tonzag_bail_truth_4";
        break;
        
        case "tonzag_bail_truth_4":
            dialog.text = "相信我, 举报信写得很巧妙。 我很擅长这类事情 —最好的诽谤是那些至少包含一点真相的诽谤。 ";
            link.l1 = "谁写的举报信? ";
            link.l1.go = "tonzag_bail_truth_a";
            link.l2 = "谁把杀手放进监狱的? ";
            link.l2.go = "tonzag_bail_truth_b";
        break;
        
        case "tonzag_bail_truth_a":
            dialog.text = "有人想让你在监狱里关几天, 而不是立即把你送到 La Roche 地下室胡格诺派的刑讯台上。 \n够了, 查尔斯。 离开吧。 先处理好眼前的事情, 之后... 嗯, 你明白我的意思! ";
            link.l1 = "是的。 我会的。 再见, 指挥官。 ";
            link.l1.go = "exit";
        break;
        
        case "tonzag_bail_truth_b":
            dialog.text = "我放的。 ";
            link.l1 = "在我离开这里之前, 你最好再派一个守卫来。 ";
            link.l1.go = "tonzag_bail_truth_b_threat";
            link.l2 = "我洗耳恭听, 指挥官。 ";
            link.l2.go = "tonzag_bail_truth_b_charm";
        break;
        
        case "tonzag_bail_truth_b_threat":
            AddComplexSelfExpToScill(100, 100, 100, 100);
        
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
                dialog.text = "我没有义务向你解释任何事情, 查尔斯。 庆幸你落到了我手里, 而不是我顶头上司的手里。 也庆幸是你的老板来补偿我所有这些麻烦, 而不是你。 ";
                link.l1 = "好吧... 你不像我那样了解我的老板。 再见, 指挥官。 ";
                link.l1.go = "exit";
				
                Notification_Skill(false, 60, SKILL_LEADERSHIP);
                AddQuestRecord("Tonzag", "3.1");
            } else {
                dialog.text = "你知道吗? 我想我会告诉你。 有人向驻军特别养老金基金慷慨捐赠了免税款项。 作为感谢, 捐赠者被允许协助迅速合法地处决一名臭名昭著的罪犯! ";
                link.l1 = "是我的军官吗? ";
                link.l1.go = "tonzag_bail_truth_b_1";
                link.l2 = "是我的朋友吗? ";
                link.l2.go = "tonzag_bail_truth_b_1";
				
                Notification_Skill(true, 60, SKILL_LEADERSHIP);
            }
        break;
        
        case "tonzag_bail_truth_b_charm":
            AddCharacterExpToSkill(pchar, "Leadership", 100);
        
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
                dialog.text = "我没有义务向你解释任何事情, 查尔斯。 庆幸你落到了我手里, 而不是我顶头上司的手里。 也庆幸是你的老板来补偿我所有这些麻烦, 而不是你。 ";
                link.l1 = "好吧... 你不像我那样了解我的老板。 再见, 指挥官。 ";
                link.l1.go = "exit";
				
                Notification_Skill(false, 60, SKILL_LEADERSHIP);
                AddQuestRecord("Tonzag", "3.1");
            } else {
                dialog.text = "你知道吗? 我想我会告诉你。 有人向驻军特别养老金基金慷慨捐赠了免税款项。 作为感谢, 捐赠者被允许协助迅速合法地处决一名臭名昭著的罪犯! ";
                link.l1 = "是我的军官吗? ";
                link.l1.go = "tonzag_bail_truth_b_1";
                link.l2 = "是我的朋友吗? ";
                link.l2.go = "tonzag_bail_truth_b_1";
				
                Notification_Skill(true, 60, SKILL_LEADERSHIP);
            }
        break;
        
        case "tonzag_bail_truth_b_1":
            dialog.text = "离开吧, 查尔斯。 把这个人渣带走。 你选择的同伴... 令人失望。 ";
            link.l1 = "至少告诉我在哪里可以找到你的... 恩人? ";
            link.l1.go = "tonzag_bail_truth_b_2";
        break;
        
        case "tonzag_bail_truth_b_2":
            dialog.text = "在大陆上。 再见, 查尔斯。 ";
            link.l1 = "";
            link.l1.go = "exit";
			
            pchar.questTemp.TonzagQuest.KnowMain = true;
            AddQuestRecord("Tonzag", "3.2");
        break;
        
        case "tonzag_bail_lies":
            dialog.text = "有人举报了你。 举报内容非常恶劣。 船长, 你显然是被陷害了, 但是... 我完全有权把你再关在这里几个星期, 让你的朋友死去。 除非... ";
            link.l1 = "要多少钱? ";
            link.l1.go = "tonzag_bail_lies_a";
            link.l2 = "谁陷害了我? 是你把杀手放进监狱的吗? ";
            link.l2.go = "tonzag_bail_lies_b";
			
            AddDialogExitQuestFunction("Tonzag_Bailed");
        break;
        
        case "tonzag_bail_lies_a":
            pchar.questTemp.TonzagQuest.Bail = 500;
            dialog.text = "请向当地放贷人缴纳五百杜布隆, 存入 托尔图加 驻军养老金基金。 ";
            if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
                pchar.questTemp.TonzagQuest.Bail = 600;
                dialog.text = dialog.text + " 再加上一百杜布隆, 算是你之前在岛上和一位高级女士纠缠不清惹出的麻烦的补偿。 ";
            }
            link.l1 = "快打开这该死的门! ";
            link.l1.go = "exit";
			
            AddQuestRecord("Tonzag", "3.3");
        break;
        
        case "tonzag_bail_lies_b":
            pchar.questTemp.TonzagQuest.Bail = 500;
            dialog.text = "你已经占用了我太多时间。 去找放贷人, 往 托尔图加 驻军养老金基金里存五百杜布隆。 ";
            if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
                pchar.questTemp.TonzagQuest.Bail = 600;
                dialog.text = dialog.text + " 再加上一百杜布隆, 算是你之前在岛上和一位高级女士纠缠不清惹出的麻烦的补偿。 ";
            }
            link.l1 = "快打开这该死的门! ";
            link.l1.go = "exit";
			
            AddQuestRecord("Tonzag", "3.3");
        break;
        
        case "tonzag_bailed":
            dialog.text = "";
            link.l1 = "钱已经存了。 赫拉克勒斯在哪里? ";
            link.l1.go = "tonzag_bailed_1";
        break;
        
        case "tonzag_bailed_1":
            dialog.text = "我们给他进行了急救, 然后把他送到你的船上去了。 这个恶棍很顽强, 很可能会挺过来。 再见, 船长, 一段时间内别让我在我们岛上再抓到你! ";
            link.l1 = "嗯, 在受到这样的接待之后, 我会离这里远远的! 再见, 指挥官。 ";
            link.l1.go = "exit";
			
            NextDiag.TempNode = "First time";
            AddDialogExitQuestFunction("Tonzag_GetOut");
        break;
        
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}