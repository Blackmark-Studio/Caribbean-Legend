// 福克斯上校 - 勇敢的海军陆战队'海狼'指挥官
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
            {
                dialog.text = "你想要什么, 先生? 哦... 我的... 等等! 你就是那位把我女儿从勒瓦瑟手下的脏手中救出来的法国船长! ";
                link.l1 = "我看凯瑟琳已经跟你说过我了... ";
                link.l1.go = "terrapin";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
            {
                dialog.text = "你想要什么, 先生? ";
                link.l1 = "日安, 上校。 我来找你是为了一些'不寻常'的事。 你能为我抽出一点时间吗? ";
                link.l1.go = "guardoftruth";
                break;
            }
            // Addon-2016 杰森, 法属圣克里斯托弗迷你任务 (FMQN) 
            if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
            {
                dialog.text = "我没猜错的话, 您就是"+GetSexPhrase("那位船长先生","那位女船长")+", 在圣马丁帮助了我的人完成任务的那位?"+TimeGreeting()+"!";
                link.l1 = TimeGreeting() + ", 上校。 是的, 正是在下。 ";
                link.l1.go = "FMQN";
                break;
            }
            dialog.text = "你想要什么, 先生? ";
            link.l1 = "没什么, 上校。 我这就告辞。 ";
            link.l1.go = "exit";            
            NextDiag.TempNode = "First time";
        break;
        
        case "guardoftruth":
            dialog.text = "既然你都已经到这步了, 那就快说吧... ";
            link.l1 = "你最近登上了一艘由荷兰海盗'帽子罗利'指挥的纵帆船, 并把船长带到了这里, 圣约翰。 ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "船长? 哦, 别让我笑掉大牙! 这个犯罪人渣根本没有资格被称为这个尊贵的头衔。 我抓到的是一个该死的海盗, 一群狼的头目, 他抢劫并谋杀了英国商人和贸易者。 我确保他和他的堕落同伙得到了应有的惩罚 —整个圣约翰的人都在码头观看了他们的绞刑! ";
            link.l1 = "我想我没法再审问这个恶棍了... 上校, 也许你能帮我? 这个海盗身上有件不属于他的东西 —黄金香炉。 你在他身上找到类似的东西了吗? ";
            link.l1.go = "guardoftruth_2";
        break;
        
        case "guardoftruth_2":
            dialog.text = "没有, 我们搜查了他, 那个无赖身上没有任何财物, 而且所有东西肯定都是从诚实的商人那里抢来的! 至于你关心的... 嗯, 没有, 我们没找到。 而且一个香炉在海盗船上能有什么用? 你真以为他们中间有牧师吗? ";
            link.l1 = "我不这么认为.'帽子罗利'从威廉斯塔德的放贷人那里买了它, 而放贷人又是从另一个海盗那里买的。 这个香炉很精致也很昂贵, 我正试图把它归还给合法的主人。 我想罗利像喜鹊一样盯上了它。 ";
            link.l1.go = "guardoftruth_3";
        break;
        
        case "guardoftruth_3":
            dialog.text = "事实上, 当我们登上并俘获他的船时, 罗利的船舱是空的, 只有几个装着达布隆金币的箱子。 除了垃圾什么都没有。 没有贵重物品, 没有黄金香炉。 我会记得这样一件不适合海盗的物品。 \n我怀疑那个该死的海盗把他的积蓄藏在多米尼加了。 我们甚至在那里登陆并搜查了那个地区, 但什么也没找到。 但由于那里有大量的野蛮人, 我们没有在岛上停留或深入探索。 ";
            link.l1 = "嗯... 这个海盗可能把香炉和他其他的赃物一起藏在多米尼加的某个地方了... 太糟糕了。 你在处决海盗之前审问过他吗? ";
            link.l1.go = "guardoftruth_4";
        break;
        
        case "guardoftruth_4":
            dialog.text = "我审问过... 他只是当着我的面笑。 但我真的不在乎他的藏匿处.'帽子罗利'被绞死了, 这是最重要的事情。 ";
            link.l1 = "我明白了。 谢谢你的讲述和时间, 上校。 再见... ";
            link.l1.go = "guardoftruth_5";
        break;
        
        case "guardoftruth_5":
            DialogExit();
            npchar.quest.utensil = "true";
            AddQuestRecord("Guardoftruth", "24");
            Island_SetReloadEnableGlobal("Dominica", true);//patch-7
            // 填充宝箱
            pchar.GenQuestBox.Shore27 = true;
            pchar.GenQuestBox.Shore27.box1.money = 30000;
            pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
            pchar.GenQuestBox.Shore27.box1.items.chest = 1;
            pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
            pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
            pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
            pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
            pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
            pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
            pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
            pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
            pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // 香炉
            pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
            pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
            pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
        break;
        
        case "terrapin":
            dialog.text = "好几次了, 船长! 你那可敬而勇敢的行为, 很难指望一个法国人能做到。 作为一名士兵和一位父亲, 我欠你一份感激之情。 在这个世界上, 没有什么比我的女儿更有价值了... ";
            link.l1 = "我很高兴能帮上忙, 我希望通过我的行动, 你能及时改变对法国人的看法。 ";
            link.l1.go = "terrapin_1";
        break;
        
        case "terrapin_1":
            dialog.text = "像你这样一位可敬而慷慨的绅士, 为了一个不熟悉的英国女孩冒生命危险, 这将使我与你的同胞的关系发生实质性的缓和! ";
            link.l1 = "任何国家的老鼠中都有诚实的人, 上校... ";
            link.l1.go = "terrapin_2";
        break;
        
        case "terrapin_2":
            dialog.text = "而你已经证明了这一点! 有一份奖励在等着你, 船长。 当然, 女儿的生命是无价的, 但乔纳森.福克斯总是会还债的, 我发誓! 你是一个真正的士兵, 因此, 我给你的礼物是一份士兵的礼物。 来, 看看。 \n这是一把滑膛枪, 一种出色的海军火枪, 可以单手使用。 你可以用特殊的箭头装载它, 这些箭头甚至可以穿透最耐用的胸甲。 它也可以发射葡萄弹, 其坚固的结构允许你用钉子装药来装载它。 拿着, 现在它是你的了。 ";
            link.l1 = "对一名士兵来说真是太棒的礼物了, 谢谢你, 上校! ";
            link.l1.go = "terrapin_3";
        break;
        
        case "terrapin_3":
            Log_Info("你获得了一把滑膛枪");
            Log_Info("你获得了10支箭");
            Log_Info("你获得了10发钉子弹药");
            Log_Info("你获得了制作鱼叉箭的说明");
            Log_Info("你获得了制作钉子弹药的说明");
            GiveItem2Character(pchar, "pistol8");
            TakeNItems(pchar, "harpoon", 10);
            TakeNItems(pchar, "GunEchin", 10);
            GiveItem2Character(pchar, "recipe_harpoon"); 
            GiveItem2Character(pchar, "recipe_GunEchin"); 
            PlaySound("interface\important_item.wav");
            dialog.text = "我还交给你一小批弹药和它们的制作说明。 如果你不最大限度地发挥它的威力, 那就太可惜了! ";
            link.l1 = "谢谢你, 上校。 我不会拒绝这样的礼物, 但我想让你知道, 我救凯瑟琳不是为了报酬。 我只是不能让这个毫无防备的女孩受到任何伤害。 ";
            link.l1.go = "terrapin_4";
        break;
        
        case "terrapin_4":
            dialog.text = "我知道, 船长。 这更让你感到荣幸。 凯瑟琳真的被你迷住了, 给她留下好印象可不是件容易的事。 再次感谢你救了她。 我欠你一个人情! ";
            link.l1 = "好吧, 谢谢你的礼物, 上校。 代我向凯瑟琳问好, 希望她下次能听她父亲的话。 ";
            link.l1.go = "terrapin_5";
        break;
        
        case "terrapin_5":
            dialog.text = "我会的, 船长! 再见, 一路平安! ";
            link.l1 = "再见, 上校。 ";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
            ChangeCharacterComplexReputation(pchar, "nobility", 5);
            ChangeCharacterComplexReputation(pchar, "fame", 5);
            ChangeCharacterNationReputation(pchar, ENGLAND, 20);
        break;
        
        // Addon-2016 杰森, 法属圣克里斯托弗迷你任务 (FMQN) 
        case "FMQN":
            DelLandQuestMark(npchar);
            dialog.text = "我已经看过报告了。 你的行为受到高度评价, 因此你必须得到奖励。 三万比索的远征服务奖励, 以及因军人英勇而获得的武器。 接受这把剑和这把火绳枪。 它们现在都是你的了! ";
            link.l1 = "谢谢你, 先生。 ";
            link.l1.go = "FMQN_1";
        break;
        
        case "FMQN_1":
            dialog.text = "当然, 船长。 你还获得了英国殖民地。 当局和我个人的爱戴和尊重。 谢谢你没有抛弃我的人, 并帮助他们完成任务! ";
            link.l1 = "我很乐意, 上校... ";
            link.l1.go = "FMQN_2";
        break;
        
        case "FMQN_2":
            dialog.text = "现在, 请原谅我 —我还有其他事情要处理。 祝你好运, 船长。 ";
            link.l1 = "再见, 先生。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("FMQN_EnglandComplete");
        break;
        
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}